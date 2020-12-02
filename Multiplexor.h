#ifndef __MULTIPLEXOR_H__
#define __MULTIPLEXOR_H__
#include <string>
using namespace std;

/*
	This class has a varible of boolean indicator outputted from Control and two data that 
*/
class Multiplexor
{
	private:
		bool controlInput;
		string dataOne;
		string dataTwo;

	public:
		Multiplexor();
		~Multiplexor();
		string getData();
		void setInput(bool ci);
		void setData(string one, string two);
};
#endif
