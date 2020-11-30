#ifndef __MULTIPLEXOR_H__
#define __MULTIPLEXOR_H__
#include <string>
using namespace std;

class Multiplexor{
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
