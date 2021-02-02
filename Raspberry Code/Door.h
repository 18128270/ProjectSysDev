#include "WemosTunnel.h"

using namespace std;

#pragma once
class Door : public WemosTunnel
{
	public:
		Door() { }
		Door(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};