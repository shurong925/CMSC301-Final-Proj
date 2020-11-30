#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__
#include<iostream>
using namespace std;

class ProgramCounter
{
 private:
   string address; //stores the result

 public:
    ProgramCounter(string Address);
    string getAddress();
};

#endif
