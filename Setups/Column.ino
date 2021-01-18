#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>

//wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

// Replace with your network credentials
const char* ssid     = "WiFi_D3_GP11";
const char* password = "GP11Wier?";

IPAddress local_IP(192,168,4,12);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

//define port for network
#define PORT 8082

// Set web server port number to 8080
WiFiServer socketServer(PORT);

int i = 0;
char buffer[100];
char outbuffer[100];

int ledstate = 0;
int buzzstate = 0;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  config_WifiConnect();
  config_PCA9554();
  config_MAX11647();
  config_SocketServer();
}

void loop() {
  
  while (i<100){
    buffer[i]= '\0';
    i++;
  }
  i = 0;
  while (i<100){
    outbuffer[i]= '\0';
    i++;
  }
  i = 0;
  // Listen for incoming clients
  WiFiClient client = socketServer.available();
  
  // pushbutton1 toggles led1
  pushButton1();

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
            LED1_on();
            sprintf(outbuffer, "%d", LED1_on());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"led1 off")){
            LED1_off();
            sprintf(outbuffer, "%d", LED1_off());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"buzzer on")){
            Buzzer_on();
            sprintf(outbuffer, "%d", Buzzer_on());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"buzzer off")){
            Buzzer_off();
            sprintf(outbuffer, "%d", Buzzer_off());
            client.write(outbuffer);
          }

          if(strstr(buffer,"check led1")){
            Check_Led1();
            sprintf(outbuffer, "%d", Check_Led1());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"check co2")){
            Check_CO2();
            sprintf(outbuffer, "%d", Check_CO2());
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

void config_WifiConnect() {
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
      Serial.println("STA Failed to configure");
  }
  
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

void config_SocketServer() {
  Serial.println("");
  Serial.print("========= Socket Server is up on port ");
  Serial.print(PORT);
  Serial.print(" =========");
  Serial.println(""); 
  socketServer.begin();
}

void pushButton1(){
  if (Check_Pushbutton1() && ledstate == 0) {
    delay(100);
    if(!(Check_Pushbutton1()) && ledstate == 0){
        LED1_on();
      }
    
  } else if(Check_Pushbutton1() && ledstate == 1){
    delay(100);
    if(!(Check_Pushbutton1()) && ledstate == 1){
        LED1_off();
      }
    
  }
}

void LED1_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
  ledstate = 1;
}

void LED1_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
  ledstate = 0;
  }

void Buzzer_on() {
  Wire.beginTransmission(0x38); //prolly needs PWM
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
  buzzstate = 1;
}

void buzzer_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
  buzzstate = 0;
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  if(Wire.read() & 0x11) { //Check output D05
    ledstate = 1;
    return 1;
  } else {
    ledstate = 0;
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
    Buzzer_on();
    return 1;
  } else {
    return 0;
  }
}
