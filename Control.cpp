#include "Control.h";

boolean Control::getRegWrite(){return RegWrite;}
boolean Control::getmemRead(){return memRead;}
boolean Control::getmemWrite(){return memWrite;}
boolean Control::getaluSrc(){return aluSrc;}
boolean Control::getRegDst(){return regDst;}
boolean Control::getJump(){return jump; }
boolean Control::getMemToReg(){return memtoReg;}

void Control::setALUop()
{
  
}

void Control::setValues()
{


}
string getALUOp(){return AlUop;}
