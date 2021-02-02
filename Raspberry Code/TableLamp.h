#include "WemosTunnel.h"

using namespace std;

#pragma once
class TableLamp : public WemosTunnel
{
	public:
		TableLamp() { }
		TableLamp(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};