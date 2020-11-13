#ifndef __ALU_H__
#define __ALU_H__

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

/* This class constructs an Arithmetic Logic Units that performs logistic computation
 * on registers passed in from RegisterFile based on ALU control and output an output
 * of 1 and 0 and result of computation.
 */

class ALU
{
 private:
   boolean zero; //If the result is zero or not
   string op; //The operation indicated by ALU Control
   string result; //The result after performing functions
   string readDataOne; //The value of first register to read
   string readDataTwo; //The value of second register to read
   string writeRegister; //The number of the register to be written to
   string writeValue; //The value to write to the write register

 public:
   ALU(); //constructor
   ~ALU(); //destructor

   void setWriteRegister(string write); //Set the number of register to be written to
   void setOperation(string operation); //Set the function to be performed based on ALU control
   void setReadDataOne(string One); //Set the number of first register to read
   void setReadDataTwo(string Two); //Set the number of second register to read

   string getWriteRegister(); //Get the number of register to be written to
   string getOperation(); //Get the operation from ALU Control
   string getResult(); //Compute the result of function performed
   string getOutput(); //Find out the output of whether it's 0 or 1
   string getWriteValue(); //Return the value to be written to the write register

};

#endif
