#include <ESP8266WiFi.h>
#include <stdlib.h>

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "WPA-2PSK";

// Set web server port number to 8080
WiFiServer socketServer(8080);

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = D5;
const int output4 = 4;
const int input0 = A0;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(input0, INPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

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
