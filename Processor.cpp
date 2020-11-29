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

int main(int argc, char *argv[])
{
  //To open the input file for reading
  fstream confg;
  confg.open(argv[1], ios::in);
  //To remind the user that the file cannot be opened
  if (!confg)
  {
      cerr << "Error: could not open file: " << argv[1] << endl;
      exit(1);
  }

  string s;
  unordered_map<string, string> config;
  while(getline(confg,s))
  {

    int equals = s.find("=");
    if(equals > 0){
      string key = s.substr(0, equals);
      string value = s.substr(equals+1);
      config[key] = value;
    }
    
  }
  confg.close();


  string program_input = config["program_input"];
  string memory_contents_input = config["memory_contents_input"];
  string register_file_input = config["register_file_input"];
  string output_mode = config["output_mode"];
  string debug = config["debug_mode"];
  string output_file = config["output_file"];
  string write = config["write_to_file"];

  bool debug_mode;
  if(debug == "false")
    debug_mode = false;
  else
    debug_mode = true;

  bool write_to_file;
  if(write == "false")
    write_to_file = false;
  else
    write_to_file = true;

  process();
  return 0;
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
