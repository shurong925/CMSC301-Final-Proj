#ifndef __SHIFTLEFT_H__
#define __SHIFTLEFT_H__

#include <stdlib.h>
#include <bitset>

using namespace std;


class ShiftLeft
{
 private:
   string result; //stores the result
    string shift; //stores the string to be shifted

 public:
   ShiftLeft(string result);
   ~ShiftLeft();
   void shiftLeftTwo(string shift);
   string getShifted();
};

#endif

