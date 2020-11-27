#include <Wire.h>

int bState;
int bStateOld;
int LEDstate;

int lightValue;
int lightValueOld;

#define I2C_SDL    D1
#define I2C_SDA    D2

void setup(void) {
  pinMode(D5, OUTPUT);
  pinMode(D7, INPUT);
  pinMode(A0, INPUT);

  Wire.begin();
  Serial.begin(115200);


}
 int delayval = 500; // delay for half a second
 // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
 

unsigned int outputs=0;
void loop(void) {
  bState = digitalRead(D7);
  lightValue = analogRead(A0);

  if (lightValue != lightValueOld) {
  Serial.println(lightValue);
  }
  
  lightValueOld = lightValue;

  if(lightValue < 400 && LEDstate == 1 || LEDstate == 2) {
    digitalWrite(D5, HIGH);
  } else {
    digitalWrite(D5, LOW);
  } 

  if(bStateOld == LOW && bState == HIGH) {
    if(LEDstate == 0) {
      //digitalWrite(D5, HIGH);
      LEDstate = 1;
    } else if (LEDstate == 1) {
      //digitalWrite(D5, LOW);
      LEDstate = 2;
    } else {
      LEDstate = 0;
    }
  }

  bStateOld = bState;

  
}
