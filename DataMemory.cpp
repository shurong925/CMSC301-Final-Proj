#include "DataMemory.h"
using namespace std;

//constructor
DataMemory::DataMemory(unordered_map<string, string> Mem)
{
  Memory = Mem;
}
//destructor
DataMemory::~DataMemory(){}

//return the data at the address
string DataMemory::read()
{
	if(memRead){
		return Memory[address];
	}
	else{
		return "";
	}
}


void DataMemory::setAddress(string add){
	address = add;
}

void DataMemory::setWriteData(string wd){
	writeData = wd;
}

void DataMemory::setMemWrite(bool mw){
	memWrite = mw;
}

void DataMemory::setMemRead(bool mr){
	memRead = mr;
}

void DataMemory::writeTheData(){
	if(memWrite){
		Memory[address] = writeData;
	}
}
unordered_map<string, string> DataMemory::getMemory(){
	return Memory;
}
