#include <ESP8266WiFi.h>
#include <stdlib.h>
#define PORT 8181


// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "PASSWORD";

// Set web server port number to 8181
WiFiServer socketServer(PORT);

const int output5 = D5;

void setup() {
  Serial.begin(115200);

  pinMode(output5, OUTPUT);
  digitalWrite(output5, LOW);

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
  Serial.print("========= Socket Server is up on port ");
  Serial.print(PORT);
  Serial.print(" =========");
  Serial.println("");
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = socketServer.available();

  // If a new client connects,
  if (client) {
    Serial.println("New Client is connected");

    // make a String (buffer) to hold incoming data from the client
    if (client) {

      while (client.connected()) {

        while (client.available() > 0) {
          //Stores buffer in string c
          char c = client.read();
          
          //prints c to monitor
          Serial.write(c);
          //writes Acknowledged back to client.
          client.write(">>> Acknowledged");
          
          if(c == '0'){
          digitalWrite(output5, HIGH);
          }
          
          if(c == '0') {
          digitalWrite(output5, LOW);
          }
          client.stop();
        }
      }
      Serial.println(" ");
      Serial.println("Client disconnected");
      //client.stop();
      }
    }
  }
