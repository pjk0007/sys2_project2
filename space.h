#include <iostream>
#include <string>
#ifndef _SPACE_H
#define _SPACE_H
using namespace std;

class space
{
	protected:
		int start_Time;
		int end_Time;
		int borrowed_Time;
		int return_Time;
		
	public:
		space();
		int getST();
		int getET();
		int getBT();
		int getRT();
};

class study_room : public space
{
	protected:
		int exist;	// 0 is already borrowed, 1 is exist

	public :
		study_room() : space(){
			start_Time = 9;
			end_Time = 18;
			exist = 1;
		}
};

class seat : public space
{
	protected:
		int remain;	// maximum 50 seats

	public :
		seat(int st, int et) : space(){
			start_Time = st;
			end_Time = et;
			remain = 0;
		}
};
#endif
