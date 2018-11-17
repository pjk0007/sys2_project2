#include <iostream>
#include <string>
#include "space.h"
using namespace std;

space::space()
{
	start_Time = 0;
	end_Time = 24;
}

int space::getST()
{
	return start_Time;
}

int space::getET()
{
	return end_Time;
}

int space::getBT()
{
	return borrowed_Time;
}

int space::getRT()
{
	return return_Time;
}
