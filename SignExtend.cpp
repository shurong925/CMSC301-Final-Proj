#include "SignExtend.h";

SignExtend::SignExtend(string Offset)
{
  offset = Offset;
}
SignExtend::~SignExtend(){}

void SignExtend::extend(string offset)
{
  extended = bitset<32> b(stoi(offset,2));
}

string SignExtend::getExtended()
{
  return extended;
}
