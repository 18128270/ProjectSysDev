#include <Wire.h>
#include <Servo.h> 

//wire.h definitions
#define I2C_SDL D1
#define I2C_SDA D2

//servo init
Servo doorServo;
//#define doorOpen position_door_open
//#define doorClose position_door_close

void setup() {
  Wire.begin();
  pinMode(D5, OUTPUT);
  
  //set servo port to D5
  doorServo.attach(D5);
}

void loop() {

}

void 

void config_PCA9554() {
  //PCA9554 configurations
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();
}

void config_MAX11647() {
  //MAX11647 configurations
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));
  Wire.endTransmission(); 
}

const char* ssid     = "SSID";
const char* password = "PASSWORD";

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

 WiFiServer socketServer(PORT);

void config_SocketServer(){
  Serial.println("");
  Serial.print("========= Socket Server is up on port ");
  Serial.print(PORT);
  Serial.print(" =========");
  Serial.println(""); 
  socketServer.begin();
}
 
//------------------Bed------------------
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
  
  if(Wire.read() & 0x10) {
    return 1;
  } else {
    return 0;
  }
}

boolean Check_pushbutton1() {
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

boolean Check_Force() {
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();

  if(anin0 >= 1000) {
    return 1;
  } else {
    return 0;
  }
}

//------------------Chair------------------
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

void Motor_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void Motor_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x10) {
    return 1;
  } else {
    return 0;
  }
}

boolean Check_Motor(){
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x11) { //Check output DO5
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
  
  if(Wire.read() & 0x01) {
    return 1;
  } else { 
    return 0; 
  }
}

boolean Check_Force() {
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();

  if(anin0 >= 1000) {
    return 1;
  } else {
    return 0;
  }
}

//------------------Column------------------
void LED1_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void LED1_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

void Buzzer_on() {
  Wire.beginTransmission(0x38); //prolly needs PWM
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void buzzer_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x11) { //Check output D05
     return 1;
  } else {
     return 0;
  }
}

boolean Check_pushbutton1() {
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

unsigned int Check_CO2(){
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();

  if(anin0 >= 1000) {
    return 1;
  } else {
    return 0;
  }
}

//------------------Door------------------
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

void LED2_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void LED2_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

void Door_open() {
  doorServo.write(90);
}

void Door_close() {
  doorServo.write(0);
}

boolean Check_Door() {
  return (doorServo.read() == 0);
}

boolean Check_Led1() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x10) {
    return 1;
  } else {
    return 0;
  }
}

boolean Check_Led2() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  
  if(Wire.read() & 0x11) {
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

//------------------Fridge------------------
boolean Check_FridgeDoor() {
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

unsigned int checkTemp1() {
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin0;
}

unsigned int checkTemp2() {
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read(); 
  unsigned int anin1 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin1;
}

//------------------Table-Lamp------------------
void LED1_on() {
  digitalWrite(D5, HIGH);
}

void LED1_off() {
  digitalWrite(D5, LOW);
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

//------------------Wall------------------
void LCD_panel_on() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void LCD_panel_off() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

void LED1_on() {
  digitalWrite(D5, HIGH);
}

void LED1_off() {
  digitalWrite(D5, LOW);
}

unsigned int Check_LDR() {
  Wire.requestFrom(0x36, 2);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin0;
}

unsigned int Check_potentiometer() {
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = ((Wire.read()&0x03) << 8) | Wire.read(); 
  unsigned int anin1 = ((Wire.read()&0x03) << 8) | Wire.read();
  return anin1;
}
