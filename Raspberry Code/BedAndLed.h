#include <iostream>
#include "string.h"
#include "WemosTunnel.h"
using namespace std;

class BedAndLed
{
	public:
		BedAndLed(string name);
		int check(string name);

	private:
		string name;
};
