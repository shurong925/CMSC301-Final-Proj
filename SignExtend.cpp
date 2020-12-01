#include "SignExtend.h"

SignExtend::SignExtend()
{
}
SignExtend::~SignExtend(){}

void SignExtend::extend(string Offset)
{
	offset = Offset;
	string extend = "000000000000000000000";
	extended = extend + offset;
  //extended = bitset<32>(stoi(offset)).to_string();
}

string SignExtend::getExtended()
{
  return extended;
}
