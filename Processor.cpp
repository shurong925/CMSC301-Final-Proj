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
  //put a loop here that does the following for every instruction in IM
  int CurrentAddress = PC.getAddress();
  cout << CurrentAddress << endl;
  //initialize the other objects that we need
  ShiftLeft SLOne = ShiftLeft();
  ShiftLeft SLTwo = ShiftLeft();
  SignExtend SE = SignExtend();
  Multiplexor MUXOne = Multiplexor();
  Multiplexor MUXTwo = Multiplexor();
  Multiplexor MUXThree = Multiplexor();
  Multiplexor MUXFour = Multiplexor();
  Multiplexor MUXFive = Multiplexor();
  ALUControl ALUC = ALUControl();
  ALU ALUOne = ALU();
  ALU AdderOne = ALU();
  AdderOne.setOperation("0010");
  ALU AdderTwo = ALU();
  AdderTwo.setOperation("0010");

  while(IM.getMap().find(CurrentAddress) != IM.getMap().end()){
    //int CurrentAddress = PC.getAddress(); this is commented out for now to avoid infinite loop
    //print output of PC
    cout << "Output of Program Counter: " <<  CurrentAddress << endl;
    IM.getAddress(CurrentAddress);
    string CurrentRS = IM.getRS();
    string CurrentRT = IM.getRT();
    string CurrentRD = IM.getRD();
    string CurrentOpCode = IM.getOpcode();
    string CurrentOffset = IM.getOffset();
    string CurrentShift = IM.getShift();
    string CurrentFunct = IM.getFunctField();
    Control.setValues(CurrentOpCode);
    cout << "\n" << endl;

    //print the input to IM
    cout << "Input to IM: the current address: " << CurrentAddress << endl;
    //print the output of IM
    cout << "Output of IM: the current RS: " << CurrentRS << endl; 
    cout << "Output of IM: the current RT: " << CurrentRT << endl; 
    cout << "Output of IM: the current RD: " << CurrentRD << endl; 
    cout << "Output of IM: the current Offset: " << CurrentOffset << endl; 
    cout << "Output of IM: the current opcode: " << CurrentOpCode << endl; 
    cout << "\n" << endl;


    //output all of the control lines (ie the input to control)
    cout << "The input to control: the control lines: " << endl;
    cout << "Value of RegWrite: " << Control.getRegWrite() << endl;
    cout << "Value of MemWrite: " << Control.getmemWrite() << endl;
    cout << "Value of ALUSrc: " << Control.getaluSrc() << endl;
    cout << "Value of RegDst: " << Control.getRegDst() << endl;
    cout << "Value of Jump: " << Control.getJump() << endl;
    cout << "Value of MemtoReg: " << Control.getMemToReg() << endl;
    cout << "Value of ALUOp: " << Control.getALUOp() << endl;
    cout << "Value of MemRead: " << Control.getmemRead() << endl; 
    cout << "\n" << endl;


    //print input to Shift left two
    SLOne.shiftLeftTwo(CurrentShift);
    cout << "The input to shift left two: " << CurrentShift << endl;
    //Print output of shift left two
    string Shifted = SLOne.getShifted();
    cout << "The output of shift left two: " << Shifted << endl;
    cout << "\n" << endl;



    //print input to multiplexor 1 (between instruction memory and registers)
    cout << "Input to multiplexor 1: " << endl;
    cout << "The current RT: " << CurrentRT << endl;
    cout << "The current RD: " << CurrentRD << endl;
    cout << "Value of RegDst: " << Control.getRegDst() << endl;
    MUXOne.setData(CurrentRT, CurrentRD);
    MUXOne.setInput(Control.getRegDst());
    //print output of multiplexor one
    cout << "Output of Multiplexor one: " << endl;
    string MUXOneData = MUXOne.getData();
    cout << "Value to be used as write register: " << MUXOneData << endl;
    cout << "\n" << endl;


    //print input to sign extend
    cout << "Input to sign extend: " << endl;
    SE.extend(CurrentOffset);
    cout << "The Current Offset: " << CurrentOffset << endl;
    //print output of sign extend
    string Extended = SE.getExtended();
    cout << "Output of sign extend: " << endl;
    cout << "Extended: " << Extended << endl;
    cout << "\n" << endl;



    //print input to register file
    //need to also implement actually writing to the registers somewhere here ***
    RF.setFirstRegister(CurrentRS);
    RF.setSecondRegister(CurrentRT);
    RF.writeInstructionOrNot(Control.getRegWrite());
    RF.setWriteRegister(MUXOneData);
    cout << "Input to Register File: " << endl;
    cout << "The current RS: " << CurrentRS << endl;
    cout << "The Current RT: " << CurrentRT << endl;
    cout << "Output of Multiplexor one: " << MUXOneData << endl;
    cout << "RegWrite value: " << Control.getRegWrite();
    cout << "\n" << endl;

    //print output of register file
    string ReadDataOne = RF.getFirstRegister();
    string ReadDataTwo = RF.getSecRegister();
    cout << "Output of Register file: " << endl;
    cout << "Read Data One: " << ReadDataOne << endl;
    cout << "Read Data Two: " << ReadDataTwo << endl;
    cout << "\n" << endl;



    //print input to to multiplexor two (in between registers and alu)
    MUXTwo.setData(ReadDataTwo, Extended);
    MUXTwo.setInput(Control.getaluSrc());
    cout << "The input to multiplexor two: " << endl;
    cout << "Read Data Two: " << ReadDataTwo << endl;
    cout << "The ALU Src: " << Control.getaluSrc() << endl;
    //print output of multiplexor two
    cout << "Output of Multiplexor two: " << endl;
    string MUXTwoData = MUXTwo.getData();
    cout << "Value to be used in ALU: " << MUXTwoData << endl;
    cout << "\n" << endl;

    //print input to ALU control
    cout << "Input to ALU control: " << endl;
    cout << "ALU Op value from control: " << Control.getALUOp() << endl;
    cout << "Funct field from Instruction memory: " << CurrentFunct << endl;
    ALUC.setFunct(CurrentFunct);
    ALUC.setALUOp(Control.getALUOp());
    //print output of ALU control
    string Operation = ALUC.getOp();
    cout << "Output of ALU control: " << endl;
    cout << "The operation to be performed: " << Operation;
    cout << "\n" << endl;


    //print input to ALU one
    cout << "Input to ALU One: " << endl;
    cout << "Read data one: " << ReadDataOne << endl;
    cout << "Output of multiplexor two: " << MUXTwoData << endl;
    cout << "Operation from ALU control: " << Operation << endl;
    ALUOne.setOperation(Operation);
    ALUOne.setReadDataOne(ReadDataOne);
    ALUOne.setReadDataTwo(MUXTwoData);
    //print output of ALU one
    string ALUOneResult = ALUOne.getResult();
    cout << "Output of ALUOne: " << endl;
    cout << "ALU One Result: " << ALUOneResult << endl;
    cout << "\n" << endl;


    //print input to data memory
    cout << "Input to data memory: " << endl;
    cout << "ALU Result: " << ALUOneResult << endl;
    cout << "Write Data: " << ReadDataTwo << endl;
    cout << "Value of MemWrite: " << Control.getmemWrite() << endl;
    cout << "Value of MemRead: "  << Control.getmemRead() << endl;
    DM.setMemWrite(Control.getmemWrite());
    DM.setMemRead(Control.getmemRead());
    DM.setAddress(ALUOneResult);
    DM.setWriteData(ReadDataTwo);
    //print output from data memory
    string DMOutput = DM.read();
    DM.writeTheData();
    cout << "Output of data memory: " << endl;
    cout << "Read data: " << DMOutput << endl;
    cout << "\n" << endl;



    //print input to multiplexor three (after data memory on far righ of diagram)
    cout << "Input to multiplexor three: " << endl;
    cout << "Output of ALU one: " << ALUOneResult << endl;
    cout << "Read data from data memory: " << DMOutput << endl;
    cout << "Value of MemToReg: " << Control.getMemToReg() << endl;
    MUXThree.setData(ALUOneResult, DMOutput);
    MUXThree.setInput(Control.getMemToReg());    
    //print output of multiplexor three
    cout << "Output of Multiplexor three: " << endl;
    string MUXThreeData = MUXThree.getData();
    cout << "Value to be used in Register File: " << MUXThreeData << endl;
    cout << "\n" << endl;

    //print input to register file (write data)
    //this is where an actual write will happen so print the write input
    cout << "Input to register file part two: " << endl;
    cout << "Write data from multiplexor three: " << MUXThreeData << endl;
    RF.setWriteValue(MUXThreeData);
    RF.write();
    cout << "\n" << endl;


    // print input to second shift left two
    cout << "Input to second shift left two: " << endl;
    cout << "Sign extended value: " << Extended << endl;
    SLTwo.shiftLeftTwo(Extended);
    string ShiftedTwo = SLTwo.getShifted();
    //print output of second shift left two
    cout << "Output of second shift left two: " << endl;
    cout << "Sign extended value shifted left by two: " << ShiftedTwo << endl;
    cout << "\n" << endl;


    //This adder is causing errors
    //print input to first adder (top left of diagram)
    cout << "Input to the first adder: " << endl;
    cout << "Address from pc: " << CurrentAddress << endl;
    cout << "Four: 4" << endl;
    //print output of firmst adder (top left of diagram)
    
    AdderOne.setReadDataOne(to_string(CurrentAddress));
    AdderOne.setReadDataTwo("0x4");
    string AdderOneResult = AdderOne.adder();
    cout << "Output of first adder: " << endl;
    cout << "PC address plus four: " << AdderOneResult << endl;
    cout << "\n" << endl;


    //this adder says the numbers are too large to add
    //print input to second adder (alu result in top right)
    cout << "Input to second adder: " << endl;
    cout << "PC address plus four: " << AdderOneResult << endl;
    cout << "Shifted two: " << ShiftedTwo << endl;
    AdderTwo.setReadDataOne(AdderOneResult);
    AdderTwo.setReadDataTwo(ShiftedTwo);
    string AdderTwoResult = AdderTwo.adder();
    //print output of second adder
    cout << "Output of second adder: " << endl;
    cout << "PC address plus jump: " << AdderTwoResult << endl;
    cout << "\n" << endl;


    //print input to multiplexor four (after alu result adder in top right of diagram)
    bool MUXFourControl;
    if(Control.getBranch() or ALUOne.getOutput()){
      MUXFourControl = true;
    }
    else{
      MUXFourControl = false;
    }
    cout << "Input to multiplexor four: " << endl;
    cout << "Output of Adder one: " << AdderOneResult << endl;
    cout << "Output of Adder two: " << AdderTwoResult << endl;
    cout << "Value of branch or zero: " << MUXFourControl << endl;
    MUXFour.setData(AdderOneResult, AdderTwoResult);
    MUXFour.setInput(MUXFourControl);    
    //print output of multiplexor four
    cout << "Output of Multiplexor four: " << endl;
    string MUXFourData = MUXFour.getData();
    cout << "Value to be used in Multiplexor five: " << MUXFourData << endl;
    cout << "\n" << endl;



    //print input to multiplexor five (top right of diagram)
    cout << "Input to multiplexor five: " << endl;
    cout << "Output of shift left one: " << ShiftedTwo << endl;
    cout << "Output of Multiplexor four: " << MUXFourData << endl;
    cout << "Value of jump: " << Control.getJump() << endl;
    MUXFive.setData(ShiftedTwo, MUXFourData);
    MUXFour.setInput(Control.getJump());    
    //print output of multiplexor five
    cout << "Output of Multiplexor five: " << endl;
    string MUXFiveData = MUXFive.getData();
    cout << "Value to be used in Program Counter five: " << MUXFiveData << endl;
    cout << "\n" << endl;

    //print input to pc
    cout << "Input to PC: " << endl;
    cout << "Output of multiplexor 5: " << MUXFiveData << endl;
    PC.setAddress(MUXFiveData);
  }
  
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

