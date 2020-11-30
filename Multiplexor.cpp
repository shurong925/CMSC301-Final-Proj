#include "Multiplexor.h"
using namespace std;

//constructor
Multiplexor::Multiplexor(){
}

//deconstructor
Multiplexor::~Multiplexor()
{	
}

string Multiplexor::getData(){
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

void Multiplexor::setData(string one, string two){
	dataOne = one;
	dataTwo = two;
}
