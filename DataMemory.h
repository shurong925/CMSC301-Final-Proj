#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
class DataMemory
{
 private:
   unordered_map<string, string> Memory; //Key is address, value is what is stored at that address
   string address; //The address to read from, from ALU
   string writeData; //The data to be written to memory, from register file


 public:
    DataMemory(unordered_map<string, string> Memory);
    ~DataMemory();
    string read(string key); //Reads the value from the stored address

};

#endif
