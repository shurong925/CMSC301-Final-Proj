#include "SignExtend.h"

SignExtend::SignExtend()
{
}
SignExtend::~SignExtend(){}

void SignExtend::extend(string Offset)
{
	offset = Offset;
  extended = bitset<32>(stoi(offset)).to_string();
}

string SignExtend::getExtended()
{
  return extended;
}
