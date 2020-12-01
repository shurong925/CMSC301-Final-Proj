#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__
#include<iostream>
using namespace std;

class ProgramCounter
{
 private:
   int address; //stores the result

 public:
    ProgramCounter();
    int getAddress();
    void setAddress(string add);
};

#endif
