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
  //write to an output file
  ofstream MyFile("output.txt");
  int CurrentAddress = PC.getAddress();
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

  while(IM.getMap().find(CurrentAddress) != IM.getMap().end())
  {
    //print output of PC
    MyFile << "Output of Program Counter: " <<  CurrentAddress << "\n";

    IM.getAddress(CurrentAddress);
    string CurrentRS = IM.getRS();
    string CurrentRT = IM.getRT();
    string CurrentRD = IM.getRD();
    string CurrentOpCode = IM.getOpcode();
    string CurrentOffset = IM.getOffset();
    string CurrentShift = IM.getShift();
    string CurrentFunct = IM.getFunctField();
    Control.setValues(CurrentOpCode);
    MyFile << "\n" << "\n";

    //print the input to IM
    MyFile << "Input to IM: the current address: " << CurrentAddress << "\n";
    MyFile << "Input to IM: the current address: ";
    MyFile << CurrentAddress;
    MyFile << "\n";
    //print the output of IM
    MyFile << "Output of IM: the current RS: " << CurrentRS << "\n";
    MyFile << "Output of IM: the current RS: " << CurrentRS << "\n";
    MyFile << "Output of IM: the current RT: " << CurrentRT << "\n";
    MyFile << "Output of IM: the current RD: " << CurrentRD << "\n";
    MyFile << "Output of IM: the current Offset: " << CurrentOffset << "\n";
    MyFile << "Output of IM: the current opcode: " << CurrentOpCode << "\n";
    MyFile << "\n" << "\n";


    //output all of the control lines (ie the input to control)
    MyFile << "The input to control: the control lines: " << "\n";
    MyFile << "Value of RegWrite: " << Control.getRegWrite() << "\n";
    MyFile << "Value of MemWrite: " << Control.getmemWrite() << "\n";
    MyFile << "Value of ALUSrc: " << Control.getaluSrc() << "\n";
    MyFile << "Value of RegDst: " << Control.getRegDst() << "\n";
    MyFile << "Value of Jump: " << Control.getJump() << "\n";
    MyFile << "Value of MemtoReg: " << Control.getMemToReg() << "\n";
    MyFile << "Value of ALUOp: " << Control.getALUOp() << "\n";
    MyFile << "Value of MemRead: " << Control.getmemRead() << "\n";
    MyFile << "\n" << "\n";


    //print input to Shift left two
    SLOne.shiftLeftTwo(CurrentShift);
    MyFile << "The input to shift left two: " << CurrentShift << "\n";
    //Print output of shift left two
    string Shifted = SLOne.getShifted();
    MyFile << "The output of shift left two: " << Shifted << "\n";
    MyFile << "\n" << "\n";

    //print input to multiplexor 1 (between instruction memory and registers)
    MyFile << "Input to multiplexor 1: " << "\n";
    MyFile << "The current RT: " << CurrentRT << "\n";
    MyFile << "The current RD: " << CurrentRD << "\n";
    MyFile << "Value of RegDst: " << Control.getRegDst() << "\n";
    MUXOne.setData(CurrentRT, CurrentRD);
    MUXOne.setInput(Control.getRegDst());
    //print output of multiplexor one
    MyFile << "Output of Multiplexor one: " << "\n";
    string MUXOneData = MUXOne.getData();
    MyFile << "Value to be used as write register: " << MUXOneData << "\n";
    MyFile << "\n" << "\n";


    //print input to sign extend
    MyFile << "Input to sign extend: " << "\n";
    SE.extend(CurrentOffset);
    MyFile << "The Current Offset: " << CurrentOffset << "\n";
    //print output of sign extend
    string Extended = SE.getExtended();
    MyFile << "Output of sign extend: " << "\n";
    MyFile << "Extended: " << Extended << "\n";
    MyFile << "\n" << "\n";


    //print input to register file
    //need to also implement actually writing to the registers somewhere here ***
    RF.setFirstRegister(CurrentRS);
    RF.setSecondRegister(CurrentRT);
    RF.writeInstructionOrNot(Control.getRegWrite());
    RF.setWriteRegister(MUXOneData);
    MyFile << "Input to Register File: " << "\n";
    MyFile << "The current RS: " << CurrentRS << "\n";
    MyFile << "The Current RT: " << CurrentRT << "\n";
    MyFile << "Output of Multiplexor one: " << MUXOneData << "\n";
    MyFile << "RegWrite value: " << Control.getRegWrite();
    MyFile << "\n" << "\n";

    //print output of register file
    string ReadDataOne = RF.getFirstRegister();
    string ReadDataTwo = RF.getSecRegister();
    MyFile << "Output of Register file: " << "\n";
    MyFile << "Read Data One: " << ReadDataOne << "\n";
    MyFile << "Read Data Two: " << ReadDataTwo << "\n";
    MyFile << "\n" << "\n";



    //print input to to multiplexor two (in between registers and alu)
    MUXTwo.setData(ReadDataTwo, Extended);
    MUXTwo.setInput(Control.getaluSrc());
    MyFile << "The input to multiplexor two: " << "\n";
    MyFile << "Read Data Two: " << ReadDataTwo << "\n";
    MyFile << "The ALU Src: " << Control.getaluSrc() << "\n";
    //print output of multiplexor two
    MyFile << "Output of Multiplexor two: " << "\n";
    string MUXTwoData = MUXTwo.getData();
    MyFile << "Value to be used in ALU: " << MUXTwoData << "\n";
    MyFile << "\n" << "\n";

    //print input to ALU control
    MyFile << "Input to ALU control: " << "\n";
    MyFile << "ALU Op value from control: " << Control.getALUOp() << "\n";
    MyFile << "Funct field from Instruction memory: " << CurrentFunct << "\n";
    ALUC.setFunct(CurrentFunct);
    ALUC.setALUOp(Control.getALUOp());
    //print output of ALU control
    string Operation = ALUC.getOp();
    MyFile << "Output of ALU control: " << "\n";
    MyFile << "The operation to be performed: " << Operation;
    MyFile << "\n" << "\n";


    //print input to ALU one
    MyFile << "Input to ALU One: " << "\n";
    MyFile << "Read data one: " << ReadDataOne << "\n";
    MyFile << "Output of multiplexor two: " << MUXTwoData << "\n";
    MyFile << "Operation from ALU control: " << Operation << "\n";
    ALUOne.setOperation(Operation);
    ALUOne.setReadDataOne(ReadDataOne);
    ALUOne.setReadDataTwo(MUXTwoData);
    //print output of ALU one
    string ALUOneResult = ALUOne.getResult();
    MyFile << "Output of ALUOne: " << "\n";
    MyFile << "ALU One Result: " << ALUOneResult << "\n";
    MyFile << "\n" << "\n";


    //print input to data memory
    MyFile << "Input to data memory: " << "\n";
    MyFile << "ALU Result: " << ALUOneResult << "\n";
    MyFile << "Write Data: " << ReadDataTwo << "\n";
    MyFile << "Value of MemWrite: " << Control.getmemWrite() << "\n";
    MyFile << "Value of MemRead: "  << Control.getmemRead() << "\n";
    DM.setMemWrite(Control.getmemWrite());
    DM.setMemRead(Control.getmemRead());
    DM.setAddress(ALUOneResult);
    DM.setWriteData(ReadDataTwo);
    //print output from data memory
    string DMOutput = DM.read();
    DM.writeTheData();
    MyFile << "Output of data memory: " << "\n";
    MyFile << "Read data: " << DMOutput << "\n";
    MyFile << "\n" << "\n";



    //print input to multiplexor three (after data memory on far righ of diagram)
    MyFile << "Input to multiplexor three: " << "\n";
    MyFile << "Output of ALU one: " << ALUOneResult << "\n";
    MyFile << "Read data from data memory: " << DMOutput << "\n";
    MyFile << "Value of MemToReg: " << Control.getMemToReg() << "\n";
    MUXThree.setData(ALUOneResult, DMOutput);
    MUXThree.setInput(Control.getMemToReg());
    //print output of multiplexor three
    MyFile << "Output of Multiplexor three: " << "\n";
    string MUXThreeData = MUXThree.getData();
    MyFile << "Value to be used in Register File: " << MUXThreeData << "\n";
    MyFile << "\n" << "\n";

    //print input to register file (write data)
    //this is where an actual write will happen so print the write input
    MyFile << "Input to register file part two: " << "\n";
    MyFile << "Write data from multiplexor three: " << MUXThreeData << "\n";
    RF.setWriteValue(MUXThreeData);
    RF.write();
    MyFile << "\n" << "\n";


    // print input to second shift left two
    MyFile << "Input to second shift left two: " << "\n";
    MyFile << "Sign extended value: " << Extended << "\n";
    SLTwo.shiftLeftTwo(Extended);
    string ShiftedTwo = SLTwo.getShifted();
    //print output of second shift left two
    MyFile << "Output of second shift left two: " << "\n";
    MyFile << "Sign extended value shifted left by two: " << ShiftedTwo << "\n";
    MyFile << "\n" << "\n";


    //print input to first adder (top left of diagram)
    MyFile << "Input to the first adder: " << "\n";
    MyFile << "Address from pc: " << CurrentAddress << "\n";
    MyFile << "Four: 4" << "\n";
    //print output of firmst adder (top left of diagram)

    AdderOne.setReadDataOne(to_string(CurrentAddress));
    AdderOne.setReadDataTwo("4");
    string AdderOneResult = AdderOne.adder(CurrentAddress, 4);
    MyFile << "Output of first adder: " << "\n";
    MyFile << "PC address plus four: " << AdderOneResult << "\n";
    MyFile << "\n" << "\n";


    //this adder says the numbers are too large to add
    //print input to second adder (alu result in top right)
    MyFile << "Input to second adder: " << "\n";
    MyFile << "PC address plus four: " << AdderOneResult << "\n";
    MyFile << "Shifted two: " << ShiftedTwo << "\n";
    string AdderTwoResult = AdderTwo.adder(stoi(AdderOneResult, 0, 2), stoi(ShiftedTwo, 0, 2));
    //print output of second adder
    MyFile << "Output of second adder: " << "\n";
    MyFile << "PC address plus jump: " << AdderTwoResult << "\n";
    MyFile << "\n" << "\n";


    //print input to multiplexor four (after alu result adder in top right of diagram)
    bool MUXFourControl;
    if(Control.getBranch() or ALUOne.getOutput()){
      MUXFourControl = true;
    }
    else{
      MUXFourControl = false;
    }
    MyFile << "Input to multiplexor four: " << "\n";
    MyFile << "Output of Adder one: " << AdderOneResult << "\n";
    MyFile << "Output of Adder two: " << AdderTwoResult << "\n";
    MyFile << "Value of branch or zero: " << MUXFourControl << "\n";
    MUXFour.setData(AdderOneResult, AdderTwoResult);
    MUXFour.setInput(MUXFourControl);
    //print output of multiplexor four
    MyFile << "Output of Multiplexor four: " << "\n";
    string MUXFourData = MUXFour.getData();
    MyFile << "Value to be used in Multiplexor five: " << MUXFourData << "\n";
    MyFile << "\n" << "\n";



    //print input to multiplexor five (top right of diagram)
    MyFile << "Input to multiplexor five: " << "\n";
    MyFile << "Output of shift left one: " << ShiftedTwo << "\n";
    MyFile << "Output of Multiplexor four: " << MUXFourData << "\n";
    MyFile << "Value of jump: " << Control.getJump() << "\n";
    MUXFive.setData(ShiftedTwo, MUXFourData);
    MUXFour.setInput(Control.getJump());
    //print output of multiplexor five
    MyFile << "Output of Multiplexor five: " << "\n";
    string MUXFiveData = MUXFive.getData();
    MyFile << "Value to be used in Program Counter: " << MUXFiveData << "\n";
    MyFile << "\n" << "\n";

    //print input to pc
    MyFile << "Input to PC: " << "\n";
    MyFile << "Output of multiplexor 5: " << MUXFiveData << "\n";
    PC.setAddress(MUXFiveData);
    CurrentAddress = PC.getAddress();

  }

  MyFile.close();
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
  int myLabelAddress = stoi("0x400000", 0, 16);
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED)
  {
    // cout << i.getString() << endl;
    instructions[myLabelAddress] = i.getEncoding();
    std::cout << myLabelAddress << endl;
    std::cout << i.getEncoding() << endl;
    i = parser->getNextInstruction();
    myLabelAddress += 4;
  }

  delete parser;
  InstructionMemory IM = InstructionMemory(instructions);
  ProgramCounter PC;

  Control Control;

  process(DM, IM, PC, RF, Control);
  return 0;

}
