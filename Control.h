#ifndef __CONTROL_H__
#define __CONTROL_H__

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

class Control
{
 private:
   String opField; //opField from the instruction memory
   Boolean RegWrite; //Indicates to register file if the instruction is a write instruction
   Boolean memRead; //Indicates to memory file if it needs to read memory and output
   Boolean memWrite; //Indicates to memory file if it needs to write memory from an input
   String ALUop; //Indicates to ALU control what the needed operation is
   Boolean aluSrc; //Indicates to mux input for ALU if the alu should use the 32 bit offset or a second value from a register when performing an operation
   Boolean regDst; //Given to input multiplexor for register file. If true, register read by register file will be in rd field, if false it comes from rt field
   Boolean jump; //If true, pc will change to the value of adder that computes branch/jump target, if false pc will increment by 4
   Boolean memtoReg; //If true, value fed to register file from data memory will be result computed by alu, if false, it will be the value grabbed from data memory Given to multiplexor that is output of data memory and input to register file


 public:
   ALU(); //constructor
   ~ALU(); //destructor

   void setValues(); //Using the opField of the instruction, sets all the boolean values
   boolean getRegWrite();
   boolean getmemRead();
   boolean getmemWrite();
   boolean getaluSrc();
   boolean getRegDst();
   boolean getJump();
   boolean getMemToReg();
   void setALUop();
   string getALUOp();
   //All of above get methods return the boolean/string value contained in data field


};

#endif
