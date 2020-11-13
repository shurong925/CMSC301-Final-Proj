#include "ALU.h";
#include "RegisterFile.h";
/*
constructor of ALU
*/
ALU::ALU(){};
/*
destructor
*/
ALU::~ALU(){};

//Set the number of register to be written to
void ALU::setWriteRegister(string write)
{
  writeRegister = write;
}

//Set the function to be performed based on ALU control
void setOperation(string operation)
{
  op = operation;
}

//Set the number of first register to read
void ALU::setReadDataOne(string One)
{
  readDataOne = One;
}

//Set the number of first register to read
void ALU::setReadDataOne(string Two)
{
  readDataTwo = Two;
}

//Get the number of register to be written to
string ALU::getWriteRegister()
{
  return writeRegister;
}

string getOperation()
{
  return op;
}

//Compute the result of function performed
string ALU::getResult()
{
  //string op;
  switch(op)
  {
  case "0010" :
     result = bitset<32> b (stoi(readDataOne,2) + stoi(readDataTwo,2));
     return result;
  case "0110" :
     result = bitset<32> b (stoi(readDataOne,2) - stoi(readDataTwo,2));
     return result;
  break;
  case "0111" :
     if(stoi(readDataOne,2) > rstoi(readDataTwo,2))
          result = readDataTwo;
     else
          result = readDataOne;
     return result;
  }

}

//Find out the output of whether it's 0 or 1
boolean ALU::getOutput()
{
  return if(result == 0);
}

//Return the value to be written to the write register
string getWriteValue()
{
  return result;
}
