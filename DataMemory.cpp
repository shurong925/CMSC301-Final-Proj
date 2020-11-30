#include "DataMemory.h"
using namespace std;

DataMemory::DataMemory(unordered_map<string, string> Mem)
{
  Memory = Mem;
}

DataMemory::~DataMemory(){}

string DataMemory::read(string key)
{
  return Memory[key];
}
