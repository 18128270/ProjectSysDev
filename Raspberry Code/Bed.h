#include "WemosTunnel.h"

using namespace std;

#pragma once
class Bed : public WemosTunnel
{
	public:
		Bed() {}
		Bed(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};