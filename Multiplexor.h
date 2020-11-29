#ifndef __MULTIPLEXOR_H__
#define __MULTIPLEXOR_H__
#include <string>
using namespace std;

class Multiplexor{
	private:
		bool controlInput;
		int dataOne;
		int dataTwo;

	public:
		Multiplexor(bool ci);
		~Multiplexor();
		int getData();
		void setInput(bool ci);
		void setData(int one, int two);
};
#endif
