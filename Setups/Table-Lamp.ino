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
#define PORT 8085

// Define static IP and gateway
IPAddress local_IP(192,168,4,15);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

// Set web server port number to 8080
WiFiServer socketServer(PORT);

#define LED_TYPE    WS2812B // Type of LED
#define COLOR_ORDER GRB     // Sequence of colors in data stream
#define NUM_LEDS    1       // Amount of LEDS numbered [0]
#define DATA_PIN    D5      // LED data pin
#define BRIGHTNESS  200     // Brightness range [OFF..ON] = [0..255]

CRGB leds[NUM_LEDS];

// init vars
int i = 0;
char buffer[100];
char outbuffer[100];
int sensorTriggered = 0; 

int ledstate = 0;
int lcdstate = 0;

unsigned long tijdNieuw;
unsigned long tijdOud;
unsigned long maxTijd = 30000;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  config_WifiConnect();
  config_PCA9554();
  config_MAX11647();
  config_SocketServer();
  
 // FastLED library init
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
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

  // check if sensor is triggered, turns led auto off after maxTijd is exceeded
  if(Check_Sensor() == 1 || ledstate == 1){
    LedAutoOff();
  }

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

          if(strstr(buffer,"check led1")){
            sprintf(outbuffer, "%d", Check_Led1());
            client.write(outbuffer);
          }

          if(strstr(buffer,"check sensor")){
            sprintf(outbuffer, "%d", Check_Sensor());
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

// TESTEN NOT WORKING PROBABLY THIS SHIT IS WACK
void LedAutoOff(){
  sensorTriggered = Check_Sensor();
  tijdNieuw = millis();
  if(sensorTriggered == 1 && ledstate == 0) {
    LED1_on();
  } else if (tijdNieuw - tijdOud >= maxTijd){
    // Led is on for too long
    LED1_off();
  }
}

void LED1_on() {
  fill_solid( &(leds[0]), 1, CRGB(250, 0, 0));
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  ledstate = 1;
}

void LED1_off() {
  FastLED.setBrightness(0);
  FastLED.show();
  ledstate = 0;
}

int Check_Led1(){
  return(digitalRead(D5));
}

boolean Check_Sensor() {
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
