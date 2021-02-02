#include "WemosTunnel.h"

using namespace std;

#pragma once
class Column : public WemosTunnel
{
public:
	Column(int DestPort, const char* DestAdd, string name) :
		DestPort(DestPort), DestAdd(DestAdd), name(name)  { }
}