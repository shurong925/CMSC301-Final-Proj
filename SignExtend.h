#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

using namespace std;
#include <stdlib.h>
#include <bitset>

class SignExtend
{
 private:
   string extended;
   string offset;

 public:
   SignExtend(string extended);
   ~SignExtend();
   void extend();
   string getExtended()
};

#endif
