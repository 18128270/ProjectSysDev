#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>

// wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

// Replace with your network credentials
const char* ssid     = "WiFi_D3_GP11";
const char* password = "GP11Wier?";

// Define port for network
#define PORT 8084

// Define static IP and gateway
IPAddress local_IP(192,168,4,14);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

// Set web server port number to PORT
WiFiServer socketServer(PORT);

// init vars
int i = 0;
char buffer[100];
char outbuffer[100];

unsigned long tijdNieuw;
unsigned long tijdOud;
unsigned long maxTijd = 20000;

int fridgedoorstate;


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

  //check if fridge door is open, if so note time
  if (Check_FridgeDoor() == 1 && tijdOud == tijdNieuw) {
    // millis() = Arduino function returns time active in unsigned Long overflows after 50 days.
    tijdOud = millis();
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
          
          if(strstr(buffer,"check fridgedoor")){
            sprintf(outbuffer, "%d", FridgeDoorAlarm());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"check temp1")){
            sprintf(outbuffer, "%d", checkTemp1());
            client.write(outbuffer);
          }
          
          if(strstr(buffer,"check temp2")){
            sprintf(outbuffer, "%d", checkTemp2());
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

int Check_FridgeDoor() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);

  if(Wire.read() & 0x01) {
    tijdNieuw = tijdOud; 
    return 0;
  } else { 
    return 1; 
  }
}

int FridgeDoorAlarm(){
//0 = DICHT, 1 = OPEN, 2 = TE LANG OPEN
  fridgedoorstate = Check_FridgeDoor();
  tijdNieuw = millis();
  if (fridgedoorstate == 0) {
    Serial.println("fridge door closed");
    return(0);
  } else if (tijdNieuw - tijdOud >= maxTijd) {
    Serial.println("fridge door open too long");
    tijdNieuw = tijdOud;
    return(2);
  } else {
    Serial.println("fridge door open");
    return(1);
  }              
}

int checkTemp1() {
  Wire.requestFrom(0x36, 2);
  int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();
  Serial.println(anin0);
  return anin0;
}

int checkTemp2() {
  Wire.requestFrom(0x36, 4);
  int anin0 = ((Wire.read()&0x03) << 8) | Wire.read(); 
  int anin1 = ((Wire.read()&0x03) << 8) | Wire.read();
  Serial.println(anin1);
  return anin1;
}
