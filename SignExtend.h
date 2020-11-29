#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

#include <stdlib.h>
#include <bitset>

using namespace std;


class SignExtend
{
 private:
   string extended;
   string offset;

 public:
   SignExtend(string extended);
   ~SignExtend();
   void extend(string offset);
   string getExtended();
};

#endif
