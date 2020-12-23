#include <Wire.h>



#define I2C_SDL    D1
#define I2C_SDA    D2

void setup(void) {
  pinMode(D5, OUTPUT);
  Wire.begin();
  Serial.begin(115200);


}
 int delayval = 500; // delay for half a second
 // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
 

unsigned int outputs=0;
void loop(void) {

  //flash mosfet output
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100); 
 
  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  //IO0-IO3 as input, IO4-IO7 as output.
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));          
  Wire.write(byte(0x0F));         
  Wire.endTransmission();
  
  //Set PCA9554 outputs (IO4-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs<<4));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);   
  outputs++;
  
  //Read PCA9554 outputs (IO0-IO3)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
  Serial.print("Digital in: ");
  Serial.println(inputs&0x0F); //output ----1111 of 16 dus niet 0/1 

  //Config MAX11647
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

  //Read analog 10bit inputs 0&1
  Wire.requestFrom(0x36, 4);   
  unsigned int anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  
  unsigned int anin1 = Wire.read()&0x03;  
  anin1=anin1<<8;
  anin1 = anin1|Wire.read(); 
  Serial.print("analog in 0: ");
  Serial.println(anin0);   
  Serial.print("analog in 1: ");
  Serial.println(anin1);   
  Serial.println("");
  
  delay(500); 

  //delay(900); 
}

