OBJS = ASM.o ASMParser.o Instruction.o Opcode.o RegisterTable.o ALU.o ALUControl.o Control.o DataMemory.o InstructionMemory.o Multiplexor.o ProgramCounter.o RegisterFile.o ShiftLeft.o SignExtend.o
CC = g++ 
CCFLAGS = -std=c++17 -Wall -Wno-deprecated -Werror=return-type -g

all:Processor

Processor: $(OBJS)
	$(CC) $(CCFLAGS) -o ASM $(OBJS)

Processor.o: Processor.cpp
	$(CC) $(CCFLAGS) -c Processor.cpp

ASMParser.o: ASMParser.cpp ASMParser.h
	$(CC) $(CCFLAGS) -c ASMParser.cpp

Instruction.o: Instruction.cpp Instruction.h
	$(CC) $(CCFLAGS) -c Instruction.cpp

Opcode.o: Opcode.cpp Opcode.h
	$(CC) $(CCFLAGS) -c Opcode.cpp

RegisterTable.o: RegisterTable.cpp RegisterTable.h
	$(CC) $(CCFLAGS) -c RegisterTable.cpp

ALU.o: ALU.cpp ALU.h
	$(CC) $(CCFLAGS) -c ALU.cpp

ALUControl.o: ALUControl.cpp ALUControl.h
	$(CC) $(CCFLAGS) -c ALUControl.cpp

Control.o: Control.cpp Control.h
	$(CC) $(CCFLAGS) -c Control.cpp

DataMemory.o: DataMemory.cpp DataMemory.h
	$(CC) $(CCFLAGS) -c DataMemory.cpp

InstructionMemory.o: InstructionMemory.cpp InstructionMemory.h
	$(CC) $(CCFLAGS) -c InstructionMemory.cpp

Multiplexor.o: Multiplexor.cpp Multiplexor.h
	$(CC) $(CCFLAGS) -c Multiplexor.cpp

ProgramCounter.o: ProgramCounter.cpp ProgramCounter.h
	$(CC) $(CCFLAGS) -c ProgramCounter.cpp

RegisterFile.o: RegisterFile.cpp RegisterFile.h
	$(CC) $(CCFLAGS) -c RegisterFile.cpp

ShiftLeft.o: ShiftLeft.cpp ShiftLeft.h
	$(CC) $(CCFLAGS) -c ShiftLeft.cpp

SignExtend.o: SignExtend.cpp SignExtend.h
	$(CC) $(CCFLAGS) -c SignExtend.cpp


clean:
	/bin/rm -f a.out Processor $(OBJS)