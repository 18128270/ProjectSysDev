#include "BedAndLed.h"
#include <iostream>

using namespace std;

BedAndLed::BedAndLed(string name)
{
	if (check(name))
	{
		WemosTunnel Tablelamp(8085, "192.168.4.15", "TableLamp");
		Tablelamp.sendCommand("led1 off");
		
	}
};

int BedAndLed::check(string name)
{
	if (name.find("Bed check force") != string::npos)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}