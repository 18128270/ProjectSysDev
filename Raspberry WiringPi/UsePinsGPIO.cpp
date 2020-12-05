//===============================================================
//  Name:          UsePinsGPIO.cpp
//  Author:         Nigel de Vos
//  Version:        1.0
//  Description:    Basic GPIO usage in C++ using export files
//===============================================================

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

using namespace std;

#define GPIO_NUMBER_A "17"
#define GPIO4_PATH_A "/sys/class/gpio/gpio17/"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(const char filename[], const char value[]){
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w+");         // open file for writing
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

int main(){

    printf("Starting the makeLED program\n");

    printf("Setting up the LED on the GPIO 2\n");
    writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER_A);

    // sleep for 100ms
    usleep(100000);

    printf("Setting up the LED on the GPIO\n");
    writeGPIO(GPIO4_PATH_A "direction", "out");
        
    for(i=0;i<10;i++){

        printf("Turning the LED of GPIO %s on\n",GPIO_NUMBER_A);
        writeGPIO(GPIO4_PATH_A "value", "1");
        
        //sleep for 1 sec
        sleep(1); 

        printf("Turning the LED of GPIO %s off\n",GPIO_NUMBER_A);
        writeGPIO(GPIO4_PATH_A "value", "0");
        
        //sleep for 1 sec
	    sleep(1);
    }

    printf("Finished the makeLED Program\n");
    return 0;
}