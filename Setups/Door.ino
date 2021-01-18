#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <Servo.h> 

// wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

// servo init
Servo doorServo;

// Replace with your network credentials
const char* ssid     = "WiFi_D3_GP11";
const char* password = "GP11Wier?";

// Define port for network
#define PORT 8083

// Define static IP and gateway
IPAddress local_IP(192,168,4,13);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

// Set web server port number to 8080
WiFiServer socketServer(PORT);

// init vars
int i = 0;
char buffer[100];
char outbuffer[100];

int ledstate1 = 0;
int ledstate2 = 0;
int doorstate = 0;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  config_WifiConnect();
  config_PCA9554();
  config_MAX11647();
  config_SocketServer();
  
  //set pin D5 as output  
  pinMode(D5, OUTPUT);

  //set servo port to D5
  doorServo.attach(D5);
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

  // pushbutton2();
  pushButton2();  

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
            client.write("ACK");
          }
          
          if(strstr(buffer,"led1 off")){
            LED1_off();
            client.write("ACK");
          }
          
          if(strstr(buffer,"led2 on")){
            LED2_on();
            client.write("ACK");
          }
          
          if(strstr(buffer,"led2 off")){
            LED2_off();
            client.write("ACK");
          }

          if(strstr(buffer,"door open")){
            Door_open();
            client.write("ACK");
          }

          if(strstr(buffer,"door close")){
            Door_close();
            client.write("ACK");
          }
          
          if(strstr(buffer,"check door")){
            sprintf(outbuffer, "%d", Check_Door());
            client.write(outbuffer);
          }

          if(strstr(buffer,"check led1")){
            sprintf(outbuffer, "%d", Check_Led1());
            client.write(outbuffer);

          if(strstr(buffer,"check led2")){
            sprintf(outbuffer, "%d", Check_Led2());
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

void config_SocketServer(){
  Serial.println("");
  Serial.print("========= Socket Server is up on port ");
  Serial.print(PORT);
  Serial.print(" =========");
  Serial.println(""); 
  socketServer.begin();
}

// TODO deze knop moet nog iets doen
void pushButton1(){
  if (Check_Pushbutton1() && /*state*/ == 0) {
    delay(100);
    if(!(Check_Pushbutton1()) && /*state*/ == 0){
        /*Functie motor*/
      }
    
  } else if (Check_Pushbutton1() && /*state*/ == 1) {
    delay(100);
    if(!(Check_Pushbutton1()) && /*state*/ == 1){
        /*Functie motor*/
      }
}

// TODO deze knop moet nog iets doen
void pushButton2(){
  if (Check_Pushbutton2() && /*state*/ == 0) {
    delay(100);
    if(!(Check_Pushbutton2()) && /*state*/ == 0){
        /*Functie motor*/
      }
    
  } else if (Check_Pushbutton2() && /*state*/ == 1) {
    delay(100);
    if(!(Check_Pushbutton2()) && /*state*/ == 1){
        /*Functie motor*/
      }
}

void LED1_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
  ledstate1 = 1;
}

void LED1_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
  ledstate1 = 0;
}

void LED2_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
  ledstate2 = 1;
}

void LED2_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
  ledstate2 = 0;
}

void Door_open() {
  // MUST TEST ====TODO====
  doorServo.write(90);
  doorstate = 1;
}

void Door_close() {
  // MUST TEST ====TODO====
  doorServo.write(0);
  doorstate = 0;
}

boolean Check_Door() {
  // MUST TEST ====TODO====
  return (doorServo.read() == 0);
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x10) {
    ledstate1 = 1;
    return 1;
  } else {
    ledstate1 = 0;
    return 0;
  }
}

boolean Check_Led2() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x20) {
    ledstate2 = 1;
    return 1;
  } else {
    ledstate2 = 0;
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

boolean Check_Pushbutton2() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x02) {
    return 1;
  } else { 
    return 0; 
  }
}
