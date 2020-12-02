#include "ALUControl.h"
using namespace std;

//constructor
ALUControl::ALUControl()
{
}

//deconstructor
ALUControl::~ALUControl()
{
}

string ALUControl::getOp(){
	return operation;
}

void ALUControl::setOp(){
	if(aluOp == "00"){
		operation = "0010"; //add
	}
	else if(aluOp == "01"){
		operation = "0110"; //subtract
	}
	else{
		if(functField == "100000"){
			operation = "0010"; //add
		}
		else if(functField == "100010"){
			operation = "0110"; //subtract
		}
		else if(functField == "100100"){
			operation = "0000"; //and
		}
		else if(functField == "100101"){
			operation = "0001"; //or
		}
		else if(functField == "101010"){
			operation = "0111"; //set on less than
		}
	}
}

void ALUControl::setALUOp(string aop){
	aluOp = aop;
	setOp(); //aluop should be gotten after the funct, so at this point we
			 //can automatically invoke setop to determine the operation
}

void ALUControl::setFunct(string funct){
	functField = funct;
}
