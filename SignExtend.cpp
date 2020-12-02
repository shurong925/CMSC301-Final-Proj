#include "SignExtend.h"

//constructor
SignExtend::SignExtend()
{
}

//destructor
SignExtend::~SignExtend()
{

}

//extend the offset to 32 bits
void SignExtend::extend(string Offset)
{
	offset = Offset;
	string extend = "000000000000000000000";
	extended = extend + offset;
}

//return the extended string
string SignExtend::getExtended()
{
  return extended;
}
