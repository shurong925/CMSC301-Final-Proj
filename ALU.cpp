#include "ALU.h"
#include "RegisterFile.h"
using namespace std;
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
void ALU::setOperation(string operation)
{
  op = operation;
}

//Set the number of first register to read
void ALU::setReadDataOne(string One)
{
  readDataOne = One;
}

//Set the number of first register to read
void ALU::setReadDataTwo(string Two)
{
  readDataTwo = Two;
}

//Get the number of register to be written to
string ALU::getWriteRegister()
{
  return writeRegister;
}

string ALU::getOperation()
{
  return op;
}

//Compute the result of function performed
string ALU::getResult()
{
  //string op;
  if(op == "0010"){
    result = bitset<32>((stoi(readDataOne, 0, 2) + stoi(readDataTwo, 0, 2))).to_string();
    return result;
  }
  else if(op == "0110"){
    result = bitset<32>((stoi(readDataOne, 0, 2) - stoi(readDataTwo, 0, 2))).to_string();
    return result;
  }
  else if(op == "0111"){
    if(stoi(readDataOne, 0, 2) > stoi(readDataTwo, 0, 2))
          result = readDataTwo;
     else
          result = readDataOne;
     return result;

  }
  return "error"; //need to figure out exactly what will happen if the ifs arent hit
}

//Find out the output of whether it's 0 or 1
bool ALU::getOutput()
{
  if(stoi(result) == 0){
    zero = true;
  }
  zero = false;
  return zero;
}

//Return the value to be written to the write register
string ALU::getWriteValue()
{
  return result;
}
