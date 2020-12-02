#ifndef __SHIFTLEFT_H__
#define __SHIFTLEFT_H__

#include <stdlib.h>
#include <bitset>

using namespace std;

/*
This class shifts left 2 bits of a binary substring
*/
class ShiftLeft
{
 private:
   string result; //stores the result
    string shift; //stores the string to be shifted

 public:
   ShiftLeft();
   ~ShiftLeft();
   void shiftLeftTwo(string shifter);
   string getShifted();
};

#endif
