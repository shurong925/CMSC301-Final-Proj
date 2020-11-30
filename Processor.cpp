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
#include "ASMParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

void process(DataMemory DM, InstructionMemory IM, ProgramCounter PC, RegisterFile RF, Control Control)
{

  int CurrentAddress = PC.getAddress();
  IM.getAddress(CurrentAddress);
  string CurrentRS = IM.getRS();
  string CurrentRT = IM.getRT();
  string CurrentRD = IM.getRD();
  string CurrentOpCode = IM.getOpcode();
  string CurrentOffset = IM.getOffset();
  //
  // bool controlInput1;
  // //if(CurrentRD == NULL)
  //   //controlInput1 = false;
  // //else
  //   //controlInput1 = true;
  //
  // Multiplexor Mul1 = Multiplexor(controlInput1);
  // Mul1.setInput(controlInput1);
  // Mul1.getData(); //Not sure how you initialize Data 1 and Data 2
  //
  // RF.setFirstRegister(CurrentRS);
  // RF.setSecondRegister(CurrentRD);
  // RF.writeInstructionOrNot(controlInput1);
  //
  // //if(RF.writeCondition() == true)
  // //{
  //  // RF.setWriteRegister(CurrentRD);
  // //}
  //
  // string firstRegister = RF.getFirstRegister();
  // string secondRegister = RF.getSecRegister();
  // string writeRegister = RF.getWriteRegister();
  //
  // string firstValue = RF.getValue(firstRegister);
  // string secondValue = RF.getValue(secondRegister);
  //
  // SignExtend SE = SignExtend(CurrentOffset);
  // string Extended = SE.getExtended();
  //
  // bool controlInput2 = false;
  // Multiplexor Mul2 = Multiplexor(controlInput1);
  // Mul1.setInput(controlInput1);
  // Mul1.getData(); //Still not sure how to use multiplexor
  //
  // string Opcode = Control.getALUOp();
  //
  // //ALUControl ALUControl();
  // //ALUControl.setOp(OpCode);
  // //string ALUOP = ALUControl.getOp();
  //
  // //ALU ALUone();
  // //ALUone.setReadDataOne(firstValue);
  // //ALUone.setReadDataTwo(); //This should be the value passed from multiplexor
  // //string Result = ALUone.getResult();
  // //string ZERO = ALUone.getOutput();
  //
  //
  //

}


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
      //std::cout<<key + ":" + value<<std::endl;
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

/////////////////////////////////////////////////////////////////////
  fstream Data;
  Data.open(memory_contents_input, ios::in);
  //To remind the user that the file cannot be opened
  if (!Data)
  {
      cerr << "Error: could not open file: " << memory_contents_input << endl;
      exit(1);
  }
  string s1;
  unordered_map<string, string> dataMemory;
  while(getline(Data,s1))
  {
    int equals = s1.find(":");
    if(equals > 0)
    {
      string key = s1.substr(0, equals);
      string value = s1.substr(equals+1);
      dataMemory[value] = key;
      //std::cout << key << " " << value << std::endl;
    }
  }
  Data.close();

  DataMemory DM = DataMemory(dataMemory);

///////////////////////////////////////////////////////////////////////
  fstream Register;
  Register.open(register_file_input, ios::in);
  if (!Register)
  {
      cerr << "Error: could not open file: " << register_file_input << endl;
      exit(1);
  }
  string s2;
  unordered_map<int, string> registerMemory;
  while(getline(Register,s2))
  {
    int equals = s2.find(":");
    if(equals > 0)
    {
      int key = std::stoi(s2.substr(0, equals));
      string value = s2.substr(equals+1);
      registerMemory[key] = value;
      //std::cout << key << std::endl;
    }
  }
  Register.close();

  unordered_map<int, string> Registers;
  for(int i = 0; i < registerMemory.size(); i++)
  {
    //std::cout << dataMemory[registerMemory[i]] << std::endl;
    Registers[i] = dataMemory[registerMemory[i]];
  }

  RegisterFile RF = RegisterFile(Registers);

/////////////////////////////////////////////////////////////////////

  ASMParser *parser;
  parser = new ASMParser(program_input);


  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;
  unordered_map<int, string> instructions; // list of Instructions
  //Iterate through instructions, printing each encoding.
  int myLabelAddress = 0x400000;
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED){
    // cout << i.getString() << endl;
    instructions[myLabelAddress] = i.getEncoding();
    i = parser->getNextInstruction();
    myLabelAddress += 4;
  }

  delete parser;
  InstructionMemory IM = InstructionMemory(instructions);

  ProgramCounter PC; //Needs symbol table to save the address of instructions

  Control Control;

  process(DM, IM, PC, RF, Control);
  return 0;


}

