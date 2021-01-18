#include <ESP8266WiFi.h>
#include <stdlib.h>
#define PORT 8080


// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "WPA2-PSK";

// Set web server port number to 8080
WiFiServer socketServer(PORT);

const int output5 = D5;

char buffer[100];
char outbuffer[100];
int i = 0;

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

void setup() {
  Serial.begin(115200);

  pinMode(output5, OUTPUT);
  digitalWrite(output5, LOW);

  config_WifiConnect();
  config_SocketServer();
}

boolean Check_Led1(){
  return 10;
}

void loop() {
  
  while (i<100){
    buffer[i]= '\0';
    i++;
  }
  i = 0;
  // Listen for incoming clients
  WiFiClient client = socketServer.available();

  // If a new client connects,
  if (client) {
    Serial.println("New Client is connected");

    // make a String (buffer) to hold incoming data from the client
    if (client) {

      while (client.connected()) {

        while (client.available() > 0) {
          char c = client.read();
          // stores multiple chars in buffer!
          if (i<100){
            buffer[i] = c;  //Stores buffer in string c
            i++;
            buffer[i] = '\0';
          }
          // check the newly made string for the commands. Bunch of if statements here.
          if(strstr(buffer,"led1 on")){
          digitalWrite(output5, HIGH);
          client.write("ACK");
          }
    
          if(strstr(buffer,"led1 off")) {
          digitalWrite(output5, LOW);
          client.write("ACK");
          }
          if(strstr(buffer,"check led1")){
          digitalRead(output5);
          sprintf(outbuffer, "%d" , digitalRead(output5));
          client.write(outbuffer);
          }
          
          if(strstr(buffer,"check pushbutton1")){
          client.write("0");
          }
          if(strstr(buffer,"check force")){
          client.write("0"); 
          }
        }
      }
      // reset the counter to account for new commands.
      i = 0;
      Serial.print("Server response: ");
      Serial.println(buffer);
      Serial.println("Client disconnected");
      } 
      Serial.println("terminating");
    }
}




  
