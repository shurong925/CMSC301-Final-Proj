#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__
#include <string>
#include <unordered_map>

using namespace std;

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

};
#endif
