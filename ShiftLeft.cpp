#include "ShiftLeft.h"

//constructor
ShiftLeft::ShiftLeft()
{
}

//destructor
ShiftLeft::~ShiftLeft()
{

}

//shift left two bits of a binary string
void ShiftLeft::shiftLeftTwo(string shifter)
{
    shift = shifter;
    result = shift.substr(2, shift.length()) + "00";
}

//return the output after shift
string ShiftLeft::getShifted()
{
  return result;
}
