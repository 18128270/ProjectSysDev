#include "WemosTunnel.h"

using namespace std;

#pragma once
class Column : public WemosTunnel
{
	public:
		Column() { }
		Column(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};