#include "Control.h"
#include "ALU.h"
#include "RegisterFile.h"
#include "ALUControl.h"
#include "DataMemory.h"
#include "Multiplexor.h"
#include "ProgramCounter.h"
#include "ShiftLeft.h"
#include "SignExtend.h"
#include "InstructionMemory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

int main()
{
  //To open the input file for reading
  std::ifstream confg(argv[0]);
  //To remind the user that the file cannot be opened
  if (!confg.is_open())
  {
      std::cerr << "Error: could not open file: " << argv[1] << std::endl;
      std::exit(1);
  }

  string s;
  vector<string> lines;
  while(getline(confg,s))
  {
    lines.push_back(s.substring(s.find_first_of(“=”)));
  }
  confg.close();

  // for(int i = 0; i < lines.length(); i++)
  // {
  //
  // }

  string program_input;
  string memory_contents_input;
  string register_file_input;
  string output_mode;
  string debug;
  string output_file;
  string write;

  boolean debug_mode;
  if(debug = "false")
    debug_mode = false;
  else
    debug_mode = true;

  boolean write_to_file;
  if(write = "false")
    write_to_file = false;
  else
    write_to_file = true;

  process();
}

void process(DataMemory DM, InstructionMemory IM, ProgramCounter PC, RegisterFile RF, Control Control)
{
  string CurrentAddress = PC.getAddress();

  string CurrentRS = IM.getRS();
  string CurrentRT = IM.getRT();
  string CurrentRD = IM.getRD();
  string CurrentOpCode = IM.getOpcode();
  string CurrentOffset = IM.getOffset();

  boolean controlInput1;
  if(CurrentRD = null)
    controlInput1 = false;
  else
    controlInput1 = true;

  Multiplexor Mul1 = Multiplexor(controlInput1);
  Mul1.setInput(contropInput1);
  Mul1.getData(); //Not sure how you initialize Data 1 and Data 2

  RF.setFirstRegister(CurrentRS);
  RF.setSecondRegister(CurrentRD);
  RF.writeInstructionOrNot(controlInput1);

  if(RF.writeCondition() == true)
  {
    RF.setWriteRegister(CurrentRD);
  }

  string 1stRegister = RF.getFirstRegister();
  string 2ndRegister = RF.getSecRegister();
  string writeRegister = RF.getWriteRegister();

  string 1stValue = RF.getValue(1stRegister);
  string 2ndValue = RF.getValue(2ndRegister);

  SignExtend SE = SignExtend(CurrentOffset);
  String Extended = SE.getExtended();

  boolean controlInput 2 = false;
  Multiplexor Mul2 = Multiplexor(controlInput1);
  Mul1.setInput(contropInput1);
  Mul1.getData(); //Still not sure how to use multiplexor

  string Opcode = Control.getALUOp();

  ALUControl ALUControl = ALUControl();
  ALUControl.setOp(OpCode);
  string ALUOP = ALUControl.getOp();

  ALU ALU1 = ALU();
  ALU1.setReadDataOne(1stValue);
  ALU1.setReadDataTwo(); //This should be the value passed from multiplexor
  string Result = ALU1.getResult();
  boolean ZERO = ALU1.getOutput();




}
