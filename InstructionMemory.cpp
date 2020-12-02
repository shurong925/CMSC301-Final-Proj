#include "InstructionMemory.h"
using namespace std;

//constructor
InstructionMemory::InstructionMemory(unordered_map<int, string> inst){
	Instructions = inst;

}

//deconstructor
InstructionMemory::~InstructionMemory()
{
}

//return the opcode
string InstructionMemory::getOpcode(){
	return currentInstruction.substr(0, 6);
}

//return RS
string InstructionMemory::getRS(){
	return currentInstruction.substr(6,5);
}

//return RT
string InstructionMemory::getRT(){
	return currentInstruction.substr(11, 5);
}

//return RD
string InstructionMemory::getRD(){
	return currentInstruction.substr(16, 5);
}

//return Offset
string InstructionMemory::getOffset(){
	return currentInstruction.substr(21, 16);
}

//return shift 
string InstructionMemory::getShift(){
	return currentInstruction.substr(6, 26);
}

void InstructionMemory::getAddress(int address){
	currentAddress = address;
	currentInstruction = Instructions[currentAddress];
}

unordered_map<int, string> InstructionMemory::getMap(){
	return Instructions;
}

string InstructionMemory::getFunctField(){
	return currentInstruction.substr(26);
}
