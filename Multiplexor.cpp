#include "Multiplexor.h"
using namespace std;

//constructor
Multiplexor::Multiplexor(bool ci){
	controlInput = ci;
}

//deconstructor
Multiplexor::~Multiplexor()
{	
}

int Multiplexor::getData(){
	if(controlInput){
		return dataOne;
	}
	else{
		return dataTwo;
	}
}

void Multiplexor::setInput(bool ci){
	controlInput = ci;
}

void Multiplexor::setData(int one, int two){
	dataOne = one;
	dataTwo = two;
}
