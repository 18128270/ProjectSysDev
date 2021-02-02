#include "WemosTunnel.h"

using namespace std;

#pragma once
class Chair : public WemosTunnel
{
	public:
		Chair() { }
		Chair(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};