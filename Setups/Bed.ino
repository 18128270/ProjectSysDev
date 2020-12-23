#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <Servo.h> 

#define I2C_SDL    D1
#define I2C_SDA    D2


// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "WPA-2PSK";

// Set web server port number to 8080
WiFiServer socketServer(8080);

void setup() {
  // Start Serial printer
  Serial.begin(115200);
  
  // Start Wire.h
  Wire.begin();
 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting...");
  }
  // Print local IP address and start Socket Server
  Serial.println("");
  Serial.print("========= WiFi connected. IP:");
  Serial.print(WiFi.localIP());
  Serial.println(" =========");
  socketServer.begin();
  Serial.println("");
  Serial.println("========= Socket Server is up on port 8080 =========");
}

void loop(){
  // Listen for incoming clients
  WiFiClient client = socketServer.available();   
  
  // If a new client connects,
  if (client) { 
    Serial.println("New Client is connected"); 
	
    // make a String (buffer) to hold incoming data from the client
	String buffer = "";                		
    if (client) {
 
    while (client.connected()) {
 
		while (client.available()>0) {
		//Stores buffer in string c  
        char c = client.read();
		//prints c to monitor
        Serial.write(c);
		//writes Acknowledged back to client.
        client.write("Acknowledged");
		}
	
		delay(10); 
    }
    Serial.println("");
	
    //Socket Server closes socket, maybe change this so the client closes the connection.
	client.stop();
    Serial.println("Client disconnected");
 
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

void LED1_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void LED1_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  uint ledState = Wire.read();  
  if (ledState & 0x01) { //00000001 dus 1
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
  uint buttonState = Wire.read();
  if (buttonState  & 0x01) {
    return true;
  } else { return false; }
}

