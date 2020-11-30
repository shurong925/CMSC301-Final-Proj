#include "ProgramCounter.h";


ProgramCounter::ProgramCounter(string Address)
{
    address = Address;
}
string ProgramCounter::getAddress()
{
    return address;
}
