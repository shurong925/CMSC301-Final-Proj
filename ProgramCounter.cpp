#include "ProgramCounter.h"


ProgramCounter::ProgramCounter()
{
    address = 0x400000;
}
int ProgramCounter::getAddress()
{
    return address;
}
