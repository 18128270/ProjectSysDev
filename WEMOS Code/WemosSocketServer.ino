#include <ESP8266WiFi.h>
#include <stdlib.h>

// Replace with your network credentials
const char* ssid     = "AIVD_SurveillanceBusje";
const char* password = "Homohol2019!";

// Set web server port number to 80
WiFiServer socketServer(8080);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = D5;
const int output4 = 4;
const int input0 = A0;

int lichtSterkte;
char* lichtSterkteString;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

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
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("========= WiFi connected. IP:");
  Serial.print(WiFi.localIP());
  Serial.println(" =========");
  socketServer.begin();
  Serial.println("");
  Serial.println("========= Socket Server is up on port 8080 =========");
}

void loop(){
  
  WiFiClient client = socketServer.available();   // Listen for incoming clients
  
  if (client) {                             // If a new client connects,
    Serial.println("New Client is connected");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        char c = client.read();
        Serial.write(c);
        client.write("Acknowledged");
       
      }
 
      delay(10); 
    }
    Serial.println("");
    client.stop();
  
    Serial.println("Client disconnected");
 
    }
  }
}
