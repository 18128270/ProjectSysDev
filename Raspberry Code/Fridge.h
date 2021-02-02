#include "WemosTunnel.h"

using namespace std;

#pragma once
class Fridge : public WemosTunnel
{
	public:
		Fridge() { }
		Fridge(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};