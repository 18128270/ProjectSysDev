#include "WemosTunnel.h"

using namespace std;

#pragma once
class Wall : public WemosTunnel
{
	public:
		Wall() { }
		Wall(int DestPort, const char* DestAdd, string name) : WemosTunnel(DestPort, DestAdd, name) { }
};