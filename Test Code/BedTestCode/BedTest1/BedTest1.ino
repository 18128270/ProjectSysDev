#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <Servo.h> 

#define I2C_SDL    D1
#define I2C_SDA    D2


void config_PCA9554() {
  //Config PCA9554
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();
  Serial.println("Config PCA Started");
}

void config_MAX11647() {
  //Config MAX11647
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));
  Wire.endTransmission(); 
  Serial.println("Config MAX Started");
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
  Wire.write(byte(0x01));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int ledState = Wire.read();  
  if (ledState & 0x10) { //Check output DO4
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
  unsigned int buttonState = Wire.read();
  if (buttonState & 0x01) { //Check input DI0
    Serial.println(buttonState);
    Serial.println(buttonState & 0x01);
    return 1;
  } else { 
    Serial.println(buttonState);
    Serial.println(buttonState & 0x01);
    return 0; }
}


void setup(){

Serial.begin(115200);
config_PCA9554();
Wire.begin();
//config_MAX11647();
}

void loop(){

  if (Check_pushbutton1()){
    Serial.println("Led1 on");
    LED1_on();
  }  else {
    Serial.println("Led1 off");
    
    LED1_off();
  }
  delay(500);
  Serial.println(Check_Led1());

}
