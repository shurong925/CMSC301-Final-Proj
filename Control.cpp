#include "Control.h"

using namespace std;

// deconstructor
Control::Control(){

}

// constructor
Control::~Control(){

}

bool Control::getRegWrite(){return RegWrite;}
bool Control::getmemRead(){return memRead;}
bool Control::getmemWrite(){return memWrite;}
bool Control::getaluSrc(){return aluSrc;}
bool Control::getRegDst(){return regDst;}
bool Control::getJump(){return jump; }
bool Control::getMemToReg(){return memtoReg;}
string Control::getALUOp(){return ALUop;}

void Control::setValues()
{
	//from table on page 269 of text
	//r - format
	if(opField == "000000"){
		regDst = true;
		aluSrc = false;
		memtoReg = false;
		RegWrite = true;
		memRead = false;
		memWrite = false;
		jump = false;
		ALUop = "10";
	}
	// lw
	else if(opField == "100011"){
		regDst = false;
		aluSrc = true;
		memtoReg = true;
		RegWrite = true;
		memRead = true;
		memWrite = false;
		jump = false;
		ALUop = "00";
	}
	// sw
	else if(opField == "101011"){
		aluSrc = true;
		RegWrite = false;
		memRead = false;
		memWrite = true;
		jump = false;
		ALUop = "00";
	}
	// beq
	else if(opField == "000100"){
		aluSrc = false;
		RegWrite = false;
		memRead = false;
		memWrite = false;
		jump = true;
		ALUop = "01";
	}

}
