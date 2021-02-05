#include "BedAndLed.h"
#include <iostream>

using namespace std;

BedAndLed::BedAndLed(string name)
{
	if (check(name))
	{
		WemosTunnel Chair(8081, "192.168.4.11", "Chair");
		Chair.sendCommand("chair motor on");
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