#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

#include <stdlib.h>
#include <bitset>

using namespace std;

/*
This class extends the binary string to 32bits
*/

class SignExtend
{
 private:
   string extended;
   string offset;

 public:
   SignExtend();
   ~SignExtend();
   void extend(string Offset);
   string getExtended();
};

#endif
