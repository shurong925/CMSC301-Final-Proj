#ifndef __ALUCONTROL_H__
#define __ALUCONTROL_H__
#include <string>
using namespace std;

class ALUControl{
	private:
		string aluOp;
		string functField;
		string operation;

	public:
		ALUControl();
		~ALUControl();
		string getOp();
		void setOp();
		void setALUOp(string aop);
		void setFunct(string funct);

};
#endif