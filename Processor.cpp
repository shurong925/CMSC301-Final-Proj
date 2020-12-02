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
//Convert hex string to binary
string hextoBin(string hexa){
   long int i = 0;
   string output = "";
   while (hexa[i]){
      switch (hexa[i]){
      case '0':
         output.append("0000");
         break;
      case '1':
         output.append("0001");
         break;
      case '2':
         output.append("0010");
         break;
      case '3':
         output.append("0011");
         break;
      case '4':
         output.append("0100");
         break;
      case '5':
         output.append("0101");
         break;
      case '6':
         output.append("0110");
         break;
      case '7':
         output.append("0111");
         break;
      case '8':
         output.append("1000");
         break;
      case '9':
         output.append("1001");
         break;
      case 'A':
      case 'a':
         output.append("1010");
         break;
      case 'B':
      case 'b':
         output.append("1011");
         break;
      case 'C':
      case 'c':
         output.append("1100");
         break;
      case 'D':
      case 'd':
         output.append("1101");
         break;
      case 'E':
      case 'e':
         output.append("1110");
         break;
      case 'F':
      case 'f':
         output.append("1111");
         break;
      default:
         cout << "please enter valid hexadecimal digit "<< hexa[i];
      }
   i++;
   }
   return output;
}

//Convert binary string to hex
string bintoHex(string bin){
  unordered_map<string, char> um;
    um["0000"] = '0';
    um["0001"] = '1';
    um["0010"] = '2';
    um["0011"] = '3';
    um["0100"] = '4';
    um["0101"] = '5';
    um["0110"] = '6';
    um["0111"] = '7';
    um["1000"] = '8';
    um["1001"] = '9';
    um["1010"] = 'A';
    um["1011"] = 'B';
    um["1100"] = 'C';
    um["1101"] = 'D';
    um["1110"] = 'E';
    um["1111"] = 'F';
    int l = bin.size();
    if(bin == ""){
      return "";
    }

    // add min 0's in the beginning to make
    // left substring length divisible by 4
    for (int i = 1; i <= (4 - l % 4) % 4; i++)
        bin = '0' + bin;

    int i = 0;
    string hex = "";

    while (1)
    {
        // one by one extract from left, substring
        // of size 4 and add its hex code
        hex += um[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;

    }

    // required hexadecimal number
    return hex;

}

void process(DataMemory DM, InstructionMemory IM, ProgramCounter PC, RegisterFile RF, Control Control, bool w, string of, unordered_map<int, string> machineInstructions, bool print_memory_contents, string output_mode)
{

  //write to an output file
  ofstream MyFile(of);
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


  while(IM.getMap().find(CurrentAddress) != IM.getMap().end()){

    if(output_mode == "single_step"){
      getchar();
    }

    IM.getAddress(CurrentAddress); //read in the current address of the instruction

    string CurrentInstruction = machineInstructions[CurrentAddress];
    string CurrentRS = IM.getRS();
    string CurrentRT = IM.getRT();
    string CurrentRD = IM.getRD();
    string CurrentOpCode = IM.getOpcode();
    string CurrentOffset = IM.getOffset();
    string CurrentShift = IM.getShift();
    string CurrentFunct = IM.getFunctField();

    Control.setValues(CurrentOpCode); //set control with the opcode read in
    SLOne.shiftLeftTwo(CurrentShift); //shift left two bits
    string Shifted = SLOne.getShifted();

    MUXOne.setData(CurrentRT, CurrentRD); //set up the first multiplexor
    MUXOne.setInput(Control.getRegDst());
    string MUXOneData = MUXOne.getData();

    SE.extend(CurrentOffset); //sign extend the current offset
    string Extended = SE.getExtended();

    RF.setFirstRegister(CurrentRS); //set up the register file to specify the register to read
    RF.setSecondRegister(CurrentRT);
    RF.writeInstructionOrNot(Control.getRegWrite());
    RF.setWriteRegister(MUXOneData);

    string ReadDataOne = hextoBin(RF.getFirstRegister()); //convert the register address to hex
    string ReadDataTwo = hextoBin(RF.getSecRegister());


    MUXTwo.setData(Extended, ReadDataTwo); //set up the second multiplexor
    MUXTwo.setInput(Control.getaluSrc());
    string MUXTwoData = MUXTwo.getData();

    ALUC.setFunct(CurrentFunct); //set up the ALU control
    ALUC.setALUOp(Control.getALUOp());
    string Operation = ALUC.getOp();

    ALUOne.setOperation(Operation); //set up the first ALU based on the opcode
    ALUOne.setReadDataOne(ReadDataOne);
    ALUOne.setReadDataTwo(MUXTwoData);
    string ALUOneResult = ALUOne.getResult(); //get the result from computation

    DM.setMemWrite(Control.getmemWrite()); //set up data memory based on the control
    DM.setMemRead(Control.getmemRead());
    DM.setAddress(bintoHex(ALUOneResult));
    DM.setWriteData(bintoHex(ReadDataTwo));

    string DMOutput = DM.read();
    DM.writeTheData(); //write data to memory

    MUXThree.setData(DMOutput, ALUOneResult); //set up the third multiplexor
    MUXThree.setInput(Control.getMemToReg());
    string MUXThreeData = MUXThree.getData();

    RF.setWriteValue(bintoHex(MUXThreeData)); //set value to be written to register file
    RF.write();

    SLTwo.shiftLeftTwo(Extended); //shift left two bits of the extended offset
    string ShiftedTwo = SLTwo.getShifted();

    string AdderOneResult = AdderOne.adder(CurrentAddress, 4); //get the result from adder
    string AdderTwoResult = AdderTwo.adder(stoi(AdderOneResult, 0, 2), stoi(ShiftedTwo, 0, 2));
    bool MUXFourControl;

    if(Control.getBranch() and ALUOne.getOutput()) //set up input for multiplexor 4
      MUXFourControl = true;
    else
      MUXFourControl = false;

    MUXFour.setData(AdderTwoResult, AdderOneResult); //set up the fourth multiplexor
    MUXFour.setInput(MUXFourControl);
    string MUXFourData = MUXFour.getData();
    MUXFive.setData(Shifted, MUXFourData);
    MUXFive.setInput(Control.getJump());
    string MUXFiveData = MUXFive.getData();
    PC.setAddress(MUXFiveData);


    //if the input config indicates that processor needs to output to file
    if(w)
    {
        MyFile << setbase(16); //set the base of output file to be in hex
        MyFile << "The Current Instruction: " << CurrentInstruction << "\n";
        MyFile << "The machine encoded instruction: " << IM.getMap()[CurrentAddress] << endl;
        MyFile << "Output of Program Counter: 0x" <<  CurrentAddress << "\n";

        MyFile << "\n" << "\n";

        //print the input to IM
        MyFile << "Input to IM: the current address: 0x" << CurrentAddress << "\n";

        MyFile << "\n";
        //print the output of IM
        MyFile << "Output of IM: the current RS: 0x" << stoi(CurrentRS,0,2) << "\n";
        MyFile << "Output of IM: the current RS: 0x" << stoi(CurrentRS, 0,2) << "\n";
        MyFile << "Output of IM: the current RT: 0x" << stoi(CurrentRT,0,2) << "\n";
        MyFile << "Output of IM: the current RD: 0x" << stoi(CurrentRD,0,2) << "\n";
        MyFile << "Output of IM: the current Offset: 0x" << stoi(CurrentOffset,0,2) << "\n";
        MyFile << "Output of IM: the current opcode: 0x" << stoi(CurrentOpCode,0,2) << "\n";
        MyFile << "\n" << endl;


        //output all of the control lines (ie the input to control)
        MyFile << "The input to control: the control lines: " << "\n";
        MyFile << "Value of RegWrite: 0x" << Control.getRegWrite() << "\n";
        MyFile << "Value of MemWrite: 0x" << Control.getmemWrite() << "\n";
        MyFile << "Value of ALUSrc: 0x" << Control.getaluSrc() << "\n";
        MyFile << "Value of RegDst: 0x" << Control.getRegDst() << "\n";
        MyFile << "Value of Jump: 0x" << Control.getJump() << "\n";
        MyFile << "Value of MemtoReg: 0x" << Control.getMemToReg() << "\n";
        MyFile << "Value of ALUOp: 0x" << Control.getALUOp() << "\n";
        MyFile << "Value of MemRead: 0x" << Control.getmemRead() << "\n";
        MyFile << "\n" << "\n";


        //print input to Shift left two
        MyFile << "The input to shift left two: 0x" << stoi(CurrentShift,0,2) << "\n";
        //Print output of shift left two
        MyFile << "The output of shift left two: 0x" << stoi(Shifted, 0, 2) << "\n";
        MyFile << "\n" << "\n";

        //print input to multiplexor 1 (between instruction memory and registers)
        MyFile << "Input to multiplexor 1: " << "\n";
        MyFile << "The current RT: 0x" << stoi(CurrentRT, 0, 2) << "\n";
        MyFile << "The current RD: 0x" << stoi(CurrentRD, 0, 2) << "\n";
        MyFile << "Value of RegDst: 0x" << Control.getRegDst() << "\n";

        //print output of multiplexor one
        MyFile << "Output of Multiplexor one: " << "\n";
        MyFile << "Value to be used as write register: 0x" << stoi(MUXOneData, 0, 2) << "\n";
        MyFile << "\n" << "\n";


        //print input to sign extend
        MyFile << "Input to sign extend: " << "\n";
        MyFile << "The Current Offset: 0x" << stoi(CurrentOffset, 0, 2) << "\n";
        //print output of sign extend
        MyFile << "Output of sign extend: " << "\n";
        MyFile << "Extended: 0x" << stoi(Extended, 0, 2) << "\n";
        MyFile << "\n" << "\n";



        //print input to register file
        //need to also implement actually writing to the registers somewhere here ***

        MyFile << "Input to Register File: " << "\n";
        MyFile << "The current RS: 0x" << stoi(CurrentRS, 0, 2) << "\n";
        MyFile << "The Current RT: 0x" << stoi(CurrentRT, 0, 2) << "\n";
        MyFile << "Output of Multiplexor one: 0x" << stoi(MUXOneData, 0, 2) << "\n";
        MyFile << "RegWrite value: 0x" << Control.getRegWrite();
        MyFile << "\n" << "\n";

        //print output of register file
        MyFile << "Output of Register file: " << "\n";
        MyFile << "Read Data One: 0x" << stoll(ReadDataOne, 0, 2) << "\n";
        //MyFile << "Read Data Two: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        MyFile << "\n" << "\n";



        //print input to to multiplexor two (in between registers and alu)

        MyFile << "The input to multiplexor two: " << "\n";
        MyFile << "Read Data Two: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        MyFile << "Sign Extended value: 0x" << stoi(Extended, 0, 2) << "\n";
        MyFile << "The ALU Src: 0x" << Control.getaluSrc() << "\n";
        //print output of multiplexor two
        MyFile << "Output of Multiplexor two: " << "\n";
        MyFile << "Value to be used in ALU: 0x" << stoll(MUXTwoData, 0, 2) << "\n";
        MyFile << "\n" << "\n";

        //print input to ALU control
        MyFile << "Input to ALU control: " << "\n";
        MyFile << "ALU Op value from control: 0x" << Control.getALUOp() << "\n";
        MyFile << "Funct field from Instruction memory: 0x" << stoi(CurrentFunct, 0, 2) << "\n";

        //print output of ALU control
        MyFile << "Output of ALU control: " << "\n";
        MyFile << "The operation to be performed: 0x" << stoi(Operation, 0, 2);
        MyFile << "\n" << "\n";


        //print input to ALU one
        MyFile << "Input to ALU One: " << "\n";
        MyFile << "Read data one: 0x" << stoll(ReadDataOne, 0, 2) << "\n";
        MyFile << "Output of multiplexor two: 0x" << stoll(MUXTwoData, 0,2) << "\n";
        MyFile << "Operation from ALU control: 0x" << stoi(Operation, 0, 2) << "\n";

        //print output of ALU one
        MyFile << "Output of ALUOne: " << "\n";
        MyFile << "ALU One Result: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        MyFile << "\n" << "\n";


        //print input to data memory
        MyFile << "Input to data memory: " << "\n";
        MyFile << "ALU Result: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        MyFile << "Write Data: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        MyFile << "Value of MemWrite: 0x" << Control.getmemWrite() << "\n";
        MyFile << "Value of MemRead: 0x"  << Control.getmemRead() << "\n";

        //print output from data memory

        MyFile << "Output of data memory: " << "\n";
        MyFile << "Read data: 0x" << DMOutput << "\n";
        MyFile << "\n" << "\n";



        //print input to multiplexor three (after data memory on far righ of diagram)
        MyFile << "Input to multiplexor three: " << "\n";
        MyFile << "Output of ALU one: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        MyFile << "Read data from data memory: 0x" << DMOutput << "\n";
        MyFile << "Value of MemToReg: 0x" << Control.getMemToReg() << "\n";

        //print output of multiplexor three
        MyFile << "Output of Multiplexor three: " << "\n";
        MyFile << "Value to be used in Register File: 0x" << MUXThreeData << "\n";
        MyFile << "\n" << "\n";

        //print input to register file (write data)
        //this is where an actual write will happen so print the write input
        MyFile << "Input to register file part two: " << "\n";
        MyFile << "Write data from multiplexor three: 0x" << MUXThreeData << "\n";

        MyFile << "\n" << "\n";


        // print input to second shift left two
        MyFile << "Input to second shift left two: " << "\n";
        MyFile << "Sign extended value: 0x" << stoi(Extended, 0, 2) << "\n";

        //print output of second shift left two
        MyFile << "Output of second shift left two: " << "\n";
        MyFile << "Sign extended value shifted left by two: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        MyFile << "\n" << "\n";


        //print input to first adder (top left of diagram)
        MyFile << "Input to the first adder: " << "\n";
        MyFile << "Address from pc: 0x" << CurrentAddress << "\n";
        MyFile << "Four: 0x4" << "\n";
        //print output of firmst adder (top left of diagram)


        MyFile << "Output of first adder: " << "\n";
        MyFile << "PC address plus four: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        MyFile << "\n" << "\n";


        //this adder says the numbers are too large to add
        //print input to second adder (alu result in top right)
        MyFile << "Input to second adder: " << "\n";
        MyFile << "PC address plus four: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        MyFile << "Shifted two: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        //print output of second adder
        MyFile << "Output of second adder: " << "\n";
        MyFile << "PC address plus jump: 0x" << stoi(AdderTwoResult, 0, 2) << "\n";
        MyFile << "\n" << "\n";


        //print input to multiplexor four (after alu result adder in top right of diagram)

        MyFile << "Input to multiplexor four: " << "\n";
        MyFile << "Output of Adder one: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        MyFile << "Output of Adder two: 0x" << stoi(AdderTwoResult, 0, 2) << "\n";
        MyFile << "Value of branch or zero: 0x" << MUXFourControl << "\n";

        //print output of multiplexor four
        MyFile << "Output of Multiplexor four: " << "\n";
        MyFile << "Value to be used in Multiplexor five: 0x" << stoi(MUXFourData, 0, 2) << "\n";
        MyFile << "\n" << "\n";

        //print input to multiplexor five (top right of diagram)
        MyFile << "Input to multiplexor five: " << "\n";
        MyFile << "Output of shift left one: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        MyFile << "Output of Multiplexor four: 0x" << stoi(MUXFourData, 0, 2) << "\n";
        MyFile << "Value of jump: 0x" << Control.getJump() << "\n";

        //print output of multiplexor five
        MyFile << "Output of Multiplexor five: " << "\n";
        MyFile << "Value to be used in Program Counter: 0x" << stoi(MUXFiveData, 0, 2) << "\n";
        MyFile << "\n" << "\n";

        //print input to pc
        MyFile << "Input to PC: " << "\n";
        MyFile << "Output of multiplexor 5: 0x" << stoi(MUXFiveData,0,2) << "\n";

      }
      //print to command line
      else
      {
        cout << setbase(16);
        cout << "The Current Instruction: " << CurrentInstruction << "\n";
        cout << "The machine encoded instruction: " << IM.getMap()[CurrentAddress] << endl;
        cout << "Output of Program Counter: 0x" <<  CurrentAddress << "\n";


        cout << "\n" << "\n";

        //print the input to IM
        cout << "Input to IM: the current address: 0x" << CurrentAddress << "\n";

        cout << "\n";
        //print the output of IM
        cout << "Output of IM: the current RS: 0x" << stoi(CurrentRS,0,2) << "\n";
        cout << "Output of IM: the current RS: 0x" << stoi(CurrentRS, 0,2) << "\n";
        cout << "Output of IM: the current RT: 0x" << stoi(CurrentRT,0,2) << "\n";
        cout << "Output of IM: the current RD: 0x" << stoi(CurrentRD,0,2) << "\n";
        cout << "Output of IM: the current Offset: 0x" << stoi(CurrentOffset,0,2) << "\n";
        cout << "Output of IM: the current opcode: 0x" << stoi(CurrentOpCode,0,2) << "\n";
        cout << "\n" << endl;


        //output all of the control lines (ie the input to control)
        cout << "The input to control: the control lines: " << "\n";
        cout << "Value of RegWrite: 0x" << Control.getRegWrite() << "\n";
        cout << "Value of MemWrite: 0x" << Control.getmemWrite() << "\n";
        cout << "Value of ALUSrc: 0x" << Control.getaluSrc() << "\n";
        cout << "Value of RegDst: 0x" << Control.getRegDst() << "\n";
        cout << "Value of Jump: 0x" << Control.getJump() << "\n";
        cout << "Value of MemtoReg: 0x" << Control.getMemToReg() << "\n";
        cout << "Value of ALUOp: 0x" << Control.getALUOp() << "\n";
        cout << "Value of MemRead: 0x" << Control.getmemRead() << "\n";
        cout << "\n" << "\n";


        //print input to Shift left two
        cout << "The input to shift left two: 0x" << stoi(CurrentShift,0,2) << "\n";
        //Print output of shift left two
        cout << "The output of shift left two: 0x" << stoi(Shifted, 0, 2) << "\n";
        cout << "\n" << "\n";



        //print input to multiplexor 1 (between instruction memory and registers)
        cout << "Input to multiplexor 1: " << "\n";
        cout << "The current RT: 0x" << stoi(CurrentRT, 0, 2) << "\n";
        cout << "The current RD: 0x" << stoi(CurrentRD, 0, 2) << "\n";
        cout << "Value of RegDst: 0x" << Control.getRegDst() << "\n";

        //print output of multiplexor one
        cout << "Output of Multiplexor one: " << "\n";
        cout << "Value to be used as write register: 0x" << stoi(MUXOneData, 0, 2) << "\n";
        cout << "\n" << "\n";


        //print input to sign extend
        cout << "Input to sign extend: " << "\n";
        cout << "The Current Offset: 0x" << stoi(CurrentOffset, 0, 2) << "\n";
        //print output of sign extend
        cout << "Output of sign extend: " << "\n";
        cout << "Extended: 0x" << stoi(Extended, 0, 2) << "\n";
        cout << "\n" << "\n";



        //print input to register file
        //need to also implement actually writing to the registers somewhere here ***

        cout << "Input to Register File: " << "\n";
        cout << "The current RS: 0x" << stoi(CurrentRS, 0, 2) << "\n";
        cout << "The Current RT: 0x" << stoi(CurrentRT, 0, 2) << "\n";
        cout << "Output of Multiplexor one: 0x" << stoi(MUXOneData, 0, 2) << "\n";
        cout << "RegWrite value: 0x" << Control.getRegWrite();
        cout << "\n" << "\n";

        //print output of register file
        cout << "Output of Register file: " << "\n";
        cout << "Read Data One: 0x" << stoll(ReadDataOne, 0, 2) << "\n";
        //cout << "Read Data Two: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        cout << "\n" << "\n";



        //print input to to multiplexor two (in between registers and alu)

        cout << "The input to multiplexor two: " << "\n";
        cout << "Read Data Two: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        cout << "Sign Extended value: 0x" << stoi(Extended, 0, 2) << "\n";
        cout << "The ALU Src: 0x" << Control.getaluSrc() << "\n";
        //print output of multiplexor two
        cout << "Output of Multiplexor two: " << "\n";
        cout << "Value to be used in ALU: 0x" << stoll(MUXTwoData, 0, 2) << "\n";
        cout << "\n" << "\n";

        //print input to ALU control
        cout << "Input to ALU control: " << "\n";
        cout << "ALU Op value from control: 0x" << Control.getALUOp() << "\n";
        cout << "Funct field from Instruction memory: 0x" << stoi(CurrentFunct, 0, 2) << "\n";

        //print output of ALU control
        cout << "Output of ALU control: " << "\n";
        cout << "The operation to be performed: 0x" << stoi(Operation, 0, 2);
        cout << "\n" << "\n";


        //print input to ALU one
        cout << "Input to ALU One: " << "\n";
        cout << "Read data one: 0x" << stoll(ReadDataOne, 0, 2) << "\n";
        cout << "Output of multiplexor two: 0x" << stoll(MUXTwoData, 0,2) << "\n";
        cout << "Operation from ALU control: 0x" << stoi(Operation, 0, 2) << "\n";

        //print output of ALU one
        cout << "Output of ALUOne: " << "\n";
        cout << "ALU One Result: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        cout << "\n" << "\n";


        //print input to data memory
        cout << "Input to data memory: " << "\n";
        cout << "ALU Result: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        cout << "Write Data: 0x" << stoll(ReadDataTwo, 0, 2) << "\n";
        cout << "Value of MemWrite: 0x" << Control.getmemWrite() << "\n";
        cout << "Value of MemRead: 0x"  << Control.getmemRead() << "\n";

        //print output from data memory

        cout << "Output of data memory: " << "\n";
        cout << "Read data: 0x" << DMOutput << "\n";
        cout << "\n" << "\n";

        //print input to multiplexor three (after data memory on far righ of diagram)
        cout << "Input to multiplexor three: " << "\n";
        cout << "Output of ALU one: 0x" << stoll(ALUOneResult, 0, 2) << "\n";
        cout << "Read data from data memory: 0x" << DMOutput << "\n";
        cout << "Value of MemToReg: 0x" << Control.getMemToReg() << "\n";

        //print output of multiplexor three
        cout << "Output of Multiplexor three: " << "\n";
        cout << "Value to be used in Register File: 0x" << MUXThreeData << "\n";
        cout << "\n" << "\n";

        //print input to register file (write data)
        //this is where an actual write will happen so print the write input
        cout << "Input to register file part two: " << "\n";
        cout << "Write data from multiplexor three: 0x" << MUXThreeData << "\n";

        cout << "\n" << "\n";


        // print input to second shift left two
        cout << "Input to second shift left two: " << "\n";
        cout << "Sign extended value: 0x" << stoi(Extended, 0, 2) << "\n";

        //print output of second shift left two
        cout << "Output of second shift left two: " << "\n";
        cout << "Sign extended value shifted left by two: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        cout << "\n" << "\n";

        //print input to first adder (top left of diagram)
        cout << "Input to the first adder: " << "\n";
        cout << "Address from pc: 0x" << CurrentAddress << "\n";
        cout << "Four: 0x4" << "\n";
        //print output of firmst adder (top left of diagram)


        cout << "Output of first adder: " << "\n";
        cout << "PC address plus four: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        cout << "\n" << "\n";

        //this adder says the numbers are too large to add
        //print input to second adder (alu result in top right)
        cout << "Input to second adder: " << "\n";
        cout << "PC address plus four: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        cout << "Shifted two: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        //print output of second adder
        cout << "Output of second adder: " << "\n";
        cout << "PC address plus jump: 0x" << stoi(AdderTwoResult, 0, 2) << "\n";
        cout << "\n" << "\n";

        //print input to multiplexor four (after alu result adder in top right of diagram)

        cout << "Input to multiplexor four: " << "\n";
        cout << "Output of Adder one: 0x" << stoi(AdderOneResult, 0, 2) << "\n";
        cout << "Output of Adder two: 0x" << stoi(AdderTwoResult, 0, 2) << "\n";
        cout << "Value of branch or zero: 0x" << MUXFourControl << "\n";

        //print output of multiplexor four
        cout << "Output of Multiplexor four: " << "\n";
        cout << "Value to be used in Multiplexor five: 0x" << stoi(MUXFourData, 0, 2) << "\n";
        cout << "\n" << "\n";

        //print input to multiplexor five (top right of diagram)
        cout << "Input to multiplexor five: " << "\n";
        cout << "Output of shift left one: 0x" << stoi(ShiftedTwo, 0, 2) << "\n";
        cout << "Output of Multiplexor four: 0x" << stoi(MUXFourData, 0, 2) << "\n";
        cout << "Value of jump: 0x" << Control.getJump() << "\n";

        //print output of multiplexor five
        cout << "Output of Multiplexor five: " << "\n";
        cout << "Value to be used in Program Counter: 0x" << stoi(MUXFiveData, 0, 2) << "\n";
        cout << "\n" << "\n";

        //print input to pc
        cout << "Input to PC: " << "\n";
        cout << "Output of multiplexor 5: 0x" << stoi(MUXFiveData,0,2) << "\n";

      }
      CurrentAddress = PC.getAddress();

  }

  if(print_memory_contents)
  {
    if(w){
      MyFile << "\n" << "\n";
      MyFile << "Registers:" << "\n";
    }
    else{
      cout << endl;
      cout << "Registers:" << endl;
    }
    for(const auto & [key, value] : RF.getRegisters()){
      if(w){
        MyFile << setbase(10);
        MyFile << key << ":" << value << "\n";
      }
      else{
        cout << setbase(10);
        cout << key << ":" << value << "\n";
      }
    }
    if(w){
      MyFile << "\n" << "\n";
      MyFile << "Data Memory:" << "\n";
    }
    else{
      cout << endl;
      cout << "Data Memory:" << endl;
    }
    for(const auto & [key, value] : DM.getMemory()){
      if(w){
        MyFile << setbase(10);
        MyFile << key << ":" << value << "\n";
      }
      else{
        cout << setbase(10);
        cout << key << ":" << value << endl;
      }
    }
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

  //store the value read from configuration file
  string program_input = config["program_input"];
  string memory_contents_input = config["memory_contents_input"];
  string register_file_input = config["register_file_input"];
  string output_mode = config["output_mode"];
  string debug = config["debug_mode"];
  string output_file = config["output_file"];
  string write = config["write_to_file"];
  string print = config["print_memory_contents"];

  bool print_memory_contents;
  if(print == "false"){
    print_memory_contents = false;
  }
  else{
    print_memory_contents = true;
  }

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

  //read in values from data memory file used to initialize DataMemory object
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

  //read in values from register file used to initialize RegisterFile object
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
    }
  }
  Register.close();
  unordered_map<int, string> Registers;
  for(int i = 0; i < registerMemory.size(); i++)
  {
    Registers[i] = dataMemory[registerMemory[i]];
  }

  RegisterFile RF = RegisterFile(registerMemory);

  //Initializ ASMParser pointer to read in the assembly file
  ASMParser *parser;
  parser = new ASMParser(program_input);

  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;
  unordered_map<int, string> instructions; // list of Instructions
  unordered_map<int, string> machineInstructions; //instructions listed in machine code
  fstream MI;
  MI.open(program_input, ios::in);
  string inst;
  int myLabelAddress = 0x400000;
  while(getline(MI,inst))
  {
    machineInstructions[myLabelAddress] = inst;
    myLabelAddress += 4;
  }
  Register.close();
  //Iterate through instructions, printing each encoding.
  myLabelAddress = 0x400000;
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED)
  {
    instructions[myLabelAddress] = i.getEncoding();
    i = parser->getNextInstruction();
    myLabelAddress += 4;
  }
  delete parser;

  //initialize instruction memory
  InstructionMemory IM = InstructionMemory(instructions);

  //initialize program counter
  ProgramCounter PC;

  //initialize control
  Control Control;

  //process the datapath
  process(DM, IM, PC, RF, Control, write_to_file, output_file,
          machineInstructions, print_memory_contents, output_mode);
  return 0;


}
