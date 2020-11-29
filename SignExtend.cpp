#include "SignExtend.h"

SignExtend::SignExtend(string Offset)
{
  offset = Offset;
}
SignExtend::~SignExtend(){}

void SignExtend::extend(string offset)
{
  extended = bitset<32>(stoi(offset)).to_string();
}

string SignExtend::getExtended()
{
  return extended;
}
