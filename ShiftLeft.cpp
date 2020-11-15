#include "ShiftLeft.h";

ShiftLeft::ShiftLeft(string Shift)
{
  shift = Shift;
}
ShiftLeft::~ShiftLeft(){}

void ShiftLeft::shiftLeftTwo(string shift)
{
    result = shift<<1
    printf("shift<<1 = %d\n", result);
}

string ShiftLeft::getShifted()
{
  return result;
}




