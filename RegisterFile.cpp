#include "RegisterFile.h"
/*
constructor of RegisterFile
@param: std::map<int, string>
*/
RegisterFile::RegisterFile(unordered_map<int, string> Collection)
{
  Registers = Collection;
}

/*
Destructor
*/
RegisterFile::~RegisterFile(){}

/*
Set the first register to be read
@param: integer of the number of register
*/
void RegisterFile::setFirstRegister(string One)
{
  readRegisterOne = One;
}

/*
Set the second register to be read
@param: integer of the number of register
*/
void RegisterFile::setSecondRegister(string Two)
{
  readRegisterTwo = Two;
}

void RegisterFile::writeInstructionOrNot(bool indicator)
{
  regWrite = indicator;
} //return indicator of whether the instruction needs to write or not

void RegisterFile::setWriteRegister(string reg)
{
  writeRegister  = reg;
} //set the register to be written to

/*
Get the number of the first register
*/
string RegisterFile::getFirstRegister()
{
  return Registers[stoi(readRegisterOne, 0, 2)];
}

/*
Get the number of the second register
*/
string RegisterFile::getSecRegister()
{
  return Registers[stoi(readRegisterTwo, 0, 2)];
}

/*
Write to the write register with data
@param: string of the value to write
*/
void RegisterFile::write()
{
  if(regWrite){
    Registers[stoi(writeRegister, 0, 2)] = writeValue;
  }
}

/*
Get the number of the write register
*/
string RegisterFile::getWriteRegister()
{
  return writeRegister;
}

/*
Get the value stored in the register
@param: integer of the number of register
*/
string RegisterFile::getValue(string index)
{
  //map<string,string > ::iterator it;
  //it = maplive.find(index);
  //return it->second;
  return "";
}

void RegisterFile::setWriteValue(string data)
{
  writeValue = data;
}

unordered_map<int, string> RegisterFile::getRegisters()
{
  return Registers;
}
