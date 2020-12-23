#include <ESP8266WiFi.h>
#include <stdlib.h>

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "WPA-2PSK";

// Set web server port number to 8080
WiFiServer socketServer(8080);

void setup() {
  Serial.begin(115200);
 
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
    client.stop();							//Socket Server closes socket, maybe change this so the client closes the connection.
  
    Serial.println("Client disconnected");
 
    }
  }
}
