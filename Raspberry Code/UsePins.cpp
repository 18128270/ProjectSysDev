//===============================================================
//  Name:           LedsTest.cpp
//  Author:         Nigel de Vos
//  Version:        1.0
//  Description:    Basic GPIO usage in C++
//===============================================================

#include <iostream>             // Include all needed libraries here
#include <wiringPi.h>

using namespace std;            // No need to keep using “std”

int main() {
wiringPiSetup();                // Setup the library
pinMode(0, OUTPUT);             // Configure GPIO0 as an output (Hardware pin 11)
pinMode(1, INPUT);              // Configure GPIO1 as an input	(Hardware pin 12)
cout << "Start"<<endl;

// Main program loop
while(1) {		
		
	// Button is pressed if digitalRead returns 0
    if(digitalRead(1) == 1){
    digitalWrite(0, !digitalRead(0));
    delay(500);
	}

}

return 0;
}


