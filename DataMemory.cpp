#include "DataMemory.h"
using namespace std;

DataMemory::DataMemory(unordered_map<string, string> Mem)
{
  Memory = Mem;
}

DataMemory::~DataMemory(){}

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

