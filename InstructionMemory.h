#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__
#include <string>
#include <unordered_map>

using namespace std;

class InstructionMemory{
	private:
		unordered_map<string, string> Instructions;
		string currentInstruction;
		string currentAddress;

	public:
		InstructionMemory(unordered_map<string, string> inst);
		~InstructionMemory();
		void getAddress(string address);
		string getOpcode();
		string getRS();
		string getRT();
		string getRD();
		string getOffset();
		string getShift();

};
#endif