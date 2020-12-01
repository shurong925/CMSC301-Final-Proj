#include "ProgramCounter.h"


ProgramCounter::ProgramCounter()
{
    address = 0x400000;
}
int ProgramCounter::getAddress()
{
    return address;
}
void ProgramCounter::setAddress(string add){
	address = stoi(add, 0, 16);
}
