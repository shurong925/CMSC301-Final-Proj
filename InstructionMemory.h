#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__
#include <string>
#include <unordered_map>

using namespace std;

/*
This class contains a collection of all instructions and has two indicators of what the current instruction is
and its address. Also, it could split an instruction into several peices for input for other objects to use.
*/
class InstructionMemory
{
	private:
		unordered_map<int, string> Instructions;
		string currentInstruction;
		int currentAddress;

	public:
		InstructionMemory(unordered_map<int, string> inst);
		~InstructionMemory();
		void getAddress(int address);
		string getOpcode();
		string getRS();
		string getRT();
		string getRD();
		string getOffset();
		string getShift();
		unordered_map<int, string> getMap();
		string getFunctField();

};
#endif
