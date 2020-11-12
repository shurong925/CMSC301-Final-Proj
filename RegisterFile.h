#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

using namespace std;

#include <iostream>
#include <string>
#include <map>

/* This class contains a collection of registers in which any register can be
 * read or written by specifying the number of the register in the file.
 */

class RegisterFile
{
 private:
   std:map<string, string> Registers; //collection of all 32 registers (Instr Memory)
   string readRegisterOne; //the first register to be read (Instr Memory)
   string readRegisterTwo; //the second register to be read (Instr Memory)
   boolean regWrite; //the boolean indicator for whether to write to a register or not (Instr Memory)
   string writeRegister; //the register to be written to (Instr Memory)

   string writeValue; //the value to be written to a register getting from ALU

 public:
   RegisterFile(std::<string, string> Registers); //constructor of RegisterFile
   ~RegisterFile(); //destructor

   void setFirstRegister(string One); //set the first register to be read
   void setSecondRegister(string Two); //set the second register to be read

   boolean writeInstructionOrNot(); //return indicator of whether the instruction needs to write or not
   void setWriteRegister(string writeRegister); //set the register to be written to

   string getFirstRegister(); //return the number of the first register
   string getSecRegister(); //return the number of the second register
   string getWriteRegister(); //return the number of the write register
   void write(); //write the value to the writeRegister

   string getValue(); //return the value stroed in a register

};

#endif
