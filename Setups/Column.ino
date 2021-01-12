#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>

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

void setup() {
  Wire.begin();
  config_WifiConnect();
}

void loop() {
  
  while (i<100){
    buffer[i]= '\0';
    i++;
  }
  // Listen for incoming clients
  WiFiClient client = socketServer.available();

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
          
          if(strstr(buffer,"led1 on")){
            client.write(LED1_on());
          }
          
          if(strstr(buffer,"led1 off")){
            client.write(LED1_off());
          }
          
          if(strstr(buffer,"buzzer on")){
            client.write(Buzzer_on());
          }
          
          if(strstr(buffer,"buzzer off")){
            client.write(Buzzer_off());
          }

          if(strstr(buffer,"check led1")){
            client.write(Check_Led1());
          }
          
          if(strstr(buffer,"check pushbutton1")){
            client.write(Check_Pushbutton1());
          }
          
          if(strstr(buffer,"check co2")){
            client.write(Check_CO2());
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

void LED1_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void LED1_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

void Buzzer_on() {
  Wire.beginTransmission(0x38); //prolly needs PWM
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void buzzer_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x11) { //Check output D05
     return 1;
  } else {
     return 0;
  }
}

boolean Check_Pushbutton1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x01) {
     return 1;
  } else {
     return 0; 
  }
}

unsigned int Check_CO2(){
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();

  if(anin0 >= 1000) {
    return 1;
  } else {
    return 0;
  }
}
