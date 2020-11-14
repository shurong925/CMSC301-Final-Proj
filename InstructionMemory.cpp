#include "InstructionMemory.h"
using namespace std;

//constructor
InstructionMemory::InstructionMemory(unordered_map<string, string> inst){
	Instructions = inst;

}

//deconstructor
InstructionMemory::~InstructionMemory()
{	
}

string InstructionMemory::getOpcode(){
	return currentInstruction.substr(0, 6);
}

string InstructionMemory::getRS(){
	return currentInstruction.substr(6,5);
}

string InstructionMemory::getRT(){
	return currentInstruction.substr(11, 5);
}

string InstructionMemory::getRD(){
	return currentInstruction.substr(16, 5);
}

string InstructionMemory::getOffset(){
	return currentInstruction.substr(21, 16);
}

string InstructionMemory::getShift(){
	return currentInstruction.substr(6, 26);
}

void InstructionMemory::getAddress(string address){
	currentAddress = address;
	currentInstruction = Instructions.at(currentAddress);
}