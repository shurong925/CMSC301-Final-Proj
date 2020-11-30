#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{
}
ShiftLeft::~ShiftLeft(){}

void ShiftLeft::shiftLeftTwo(string shifter)
{
    shift = shifter;
    result = shift.substr(2, shift.length()) + "00";
}

string ShiftLeft::getShifted()
{
  return result;
}




