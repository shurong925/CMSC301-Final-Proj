#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

using namespace std;

#include <iostream>
#include <string>
#include <map>

class DataMemory
{
 private:
   std:map<string, string> Memory; //Key is address, value is what is stored at that address
   string address; //The address to read from, from ALU
   string writeData; //The data to be written to memory, from register file
   boolean memWrite; //Value from control that indicates if the instruction is a write
    boolean memRead; //Value from control that indicates if the instruction is a read
    
 public:
    string read(); //Reads the value from the stored address
    void write(string writeValue, int writeRegister); //If there is a value needed to be written to memory, set the address value to become the new value - just insert and remove from the map

};

#endif
