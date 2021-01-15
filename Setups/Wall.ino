#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <Servo.h> 

//wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "WPA-2PSK";

//define port for network
#define PORT 8080

// Set web server port number to 8080
WiFiServer socketServer(PORT);

int i = 0;
char buffer[100];
char outbuffer[100];

int ledstate = 0;
int lcdstate = 0;

void setup() {
  Wire.begin();
  config_WifiConnect();
  
  //set pin D5 as output  
  pinMode(D5, OUTPUT);
}

void loop() {
  
  while (i<100){
    buffer[i]= '\0';
    i++;
  }
  while (i<100){
    outbuffer[i]= '\0';
    i++;
  }

  // Listen for incoming clients
  WiFiClient client = socketServer.available();

  // if ldr too damn high auto dim dus lcd = 1;

  // If a new client connects,
  if (client) {
    Serial.println("New Client is connected");

    if (client) {

     while (client.connected()) {

        while (client.available() > 0) {
          //Stores buffer in string c
          char c = client.read();
          
          if (i<100){
            buffer[i] = c;  //Stores buffer in string c
            i++;
            buffer[i] = '\0';
          }

          if(strstr(buffer,"lcd on")){
            client.write(LCD_panel_on());
          }

          if(strstr(buffer,"lcd off")){
            client.write(LCD_panel_off());
          }
          
          if(strstr(buffer,"led1 on")){
            LED1_on();
            client.write("ACK");
          }
          
          if(strstr(buffer,"led1 off")){
            LED1_off();
            client.write("ACK");
          }

          if(strstr(buffer,"check led1")){
            sprintf(outbuffer, "%d", Check_Led1();
            client.write(outbuffer);
          }

          if(strstr(buffer,"check ldr")){
            sprintf(outbuffer, "%d", Check_LDR());
            client.write(outbuffer);
          }

          if(strstr(buffer,"check potmeter")){
            sprintf(outbuffer, "%d", Check_Potentiometer());
            client.write(outbuffer);
          }
        }
      }
    Serial.println(" ");
    Serial.println("Client disconnected");
    i = 0;
    }
  }
}

void config_PCA9554() {
  //Config PCA9554
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();
}

void config_MAX11647() {
  //Config MAX11647
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));
  Wire.endTransmission(); 
}

void config_WifiConnect(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting...");
  }
  Serial.println("");
  Serial.print("========= WiFi connected. IP:");
  Serial.print(WiFi.localIP());
  Serial.println(" =========");
}

void config_SocketServer(){
  Serial.println("");
  Serial.print("========= Socket Server is up on port ");
  Serial.print(PORT);
  Serial.print(" =========");
  Serial.println(""); 
  socketServer.begin();
}



void LCD_panel_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
  lcdstate = 1;
}

void LCD_panel_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
  lcdstate = 0;
}

void LED1_on() {
  digitalWrite(D5, HIGH);
  ledstate = 1;
}

void LED1_off() {
  digitalWrite(D5, LOW);
  ledstate = 0;
}

boolean Check_Led1(){
  return digitalRead(D5);
}

boolean Check_LCD(){
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.requestFrom(0x38, 1);

  if(Wire.read() & 0x10){
    lcdstate = 1;
    return 1;
  } else {
    lcdstate = 0;
    return 0;
  }
}

unsigned int Check_LDR() {
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin0;
}

unsigned int Check_Potentiometer() {
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read(); 
  unsigned int anin1 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin1;
}
