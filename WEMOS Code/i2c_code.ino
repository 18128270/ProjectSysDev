#include <Wire.h>
#include <Servo.h> 

#define I2C_SDL    D1
#define I2C_SDA    D2

//Door
Servo deurServo;
#define deurOpen positie_deur_open
#define deurDicht positie_deur_dicht

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  
  //init servo (door)
  deurServo.attach(D5);
}

void loop() {
  // put your main code here, to run repeatedly:

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

//------------------Table-Lamp------------------
void LED_aan() {
  
}

void LED_uit() {
  
}

//------------------Door------------------
void LED1_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void LED1_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

void LED2_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void LED2_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

void Deur_open() {
  deurServo.write(deurOpen);
}

void Deur_dicht() {
  deurServo.write(deurDicht);
}

boolean Check_pushbutton1 {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 0);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

boolean Check_pushbutton2 {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

//------------------Fridge------------------
void fan_snelheid(uint8_t snelheid) {
  
}

void Peltier_aan() {
  digitalWrite(D5, HIGH);
}

void Peltier_uit() {
  digitalWrite(D5, LOW);
}

boolean Check_switch {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 0);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

int checkTemperatuur1 {
  
}

//------------------Chair------------------
void LED1_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void LED1_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

void Motor_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

void Motor_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

boolean Check_pushbutton1 {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 0);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

//------------------Bed------------------
void LED1_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void LED1_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}

boolean Check_pushbutton1 {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

//------------------Column------------------
void LED1_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<5));
  Wire.endTransmission();
}

boolean Check_pushbutton1 {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 0);   
  unsigned int buttonStaat = Wire.read();
  if (buttonStaat == 1) {
    return true;
  } else { return false; }
}

void LED1_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<5));
  Wire.endTransmission();
}

void Buzzer_aan() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x01<<4));
  Wire.endTransmission();
}

void buzzer_uit() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));
  Wire.write(byte(0x00<<4));
  Wire.endTransmission();
}
