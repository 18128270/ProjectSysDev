#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <FastLED.h>

// wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

// Replace with your network credentials
const char* ssid     = "WiFi_D3_GP11";
const char* password = "GP11Wier?";

// Define port for network
#define PORT 8086

// Define staic IP and gateway
IPAddress local_IP(192,168,4,16);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

// Set web server port number to 8080
WiFiServer socketServer(PORT);

#define LED_TYPE    WS2812B // Type of LED
#define COLOR_ORDER GRB     // Sequence of colors in data stream
#define NUM_LEDS    3       // Amount of LEDS numbered [0..2]
#define DATA_PIN    D5      // LED data pin
#define BRIGHTNESS  200     // Brightness range [OFF..ON] = [0..255]

CRGB Leds[NUM_LEDS];

// init vars
int i = 0;
char buffer[100];
char outbuffer[100];
int color = 0;

int ledstate = 0;
int lcdstate = 0;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  config_WifiConnect();
  config_PCA9554();
  config_MAX11647();
  config_SocketServer();
  
  // FastLED library init
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(Leds, NUM_LEDS);
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

  // === MUST TEST === Potmeter changes LED colour hopefully
  SetColour();
  
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
            LCD_panel_on();
            client.write("ACK");
          }

          if(strstr(buffer,"lcd off")){
            LCD_panel_off();
            client.write("ACK");
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
            sprintf(outbuffer, "%d", Check_Led1());
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
  fill_solid( &(Leds[0]), 3, CRGB(250, 0, 0));
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  ledstate = 1;
}

void LED1_off() {
  FastLED.setBrightness(0);
  FastLED.show();
  ledstate = 0;
}

boolean Check_Led1(){
  return (ledstate);
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

void SetColour(){
  int val = Check_Potentiometer();
  int R;
  int G;
  int B;

  if (val < 341) {
    color = val % 341;
    if (color>255){
      color = 255;
    }
    color = val;
    R = color;
    G = 0;
    B = 0;
  }
  if (341 >= val < 682) {
    color = val % 341;
    if (color>255){
      color = 255;
    }
    R = 0;
    G = color;
    B = 0;
  }
  if (val >= 682) {
    color = val % 341;
    if (color>255){
      color = 255;
    }
    R = 0;
    G = 0;
    B = color;
  }
  fill_solid( &(Leds[0]), 3 /*number of leds*/, CRGB(R, G, B));
  FastLED.show();
}

int Check_LDR() {
  Wire.requestFrom(0x36, 2);
  int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();
  if(anin0>600){
    LCD_panel_on();
  }else{
    LCD_panel_off();
  }
  return anin0;
}

int Check_Potentiometer() {
  Wire.requestFrom(0x36, 4);
  int anin0 = ((Wire.read()&0x03) << 8) | Wire.read(); 
  int anin1 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin1;
}
