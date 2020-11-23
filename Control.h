#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

/* This class constructs an Arithmetic Logic Units that performs logistic computation
 * on registers passed in from RegisterFile based on ALU control and output an output
 * of 1 and 0 and result of computation.
 */

class Control
{
 private:
   string opField; //opField from the instruction memory
   bool RegWrite; //Indicates to register file if the instruction is a write instruction
   bool memRead; //Indicates to memory file if it needs to read memory and output
   bool memWrite; //Indicates to memory file if it needs to write memory from an input
   string ALUop; //Indicates to ALU control what the needed operation is
   bool aluSrc; //Indicates to mux input for ALU if the alu should use the 32 bit offset or a second value from a register when performing an operation
   bool regDst; //Given to input multiplexor for register file. If true, register read by register file will be in rd field, if false it comes from rt field
   bool jump; //If true, pc will change to the value of adder that computes branch/jump target, if false pc will increment by 4
   bool memtoReg; //If true, value fed to register file from data memory will be result computed by alu, if false, it will be the value grabbed from data memory Given to multiplexor that is output of data memory and input to register file


 public:
   Control(); //constructor
   ~Control(); //destructor

   void setValues(); //Using the opField of the instruction, sets all the boolean values
   bool getRegWrite();
   bool getmemRead();
   bool getmemWrite();
   bool getaluSrc();
   bool getRegDst();
   bool getJump();
   bool getMemToReg();
   string getALUOp();
   //All of above get methods return the boolean/string value contained in data field


};
#endif
