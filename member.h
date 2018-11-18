#include <iostream>
#include <string>
#ifndef _MEMBER_H
#define _MEMBER_H
using namespace std;

class member
{
	protected:
		string mem_Name;
		string Type;
		int canBorrow;
		int nowBorrow;
		int ban_year;
		int ban_month;
		int ban_day;
		int term;

		int seat_time_limit;
		int room;	// already borrowed 1, no borrowed 0
		int room_num;
		int seat;	// already borrowd 1, no borrowed 0
		int seat_num;
		int room_time;
		int seat_time;

		
	public:
		member(string mn, string T);
		string getName();
		int getBorrow();
		int getYear();
		int getMonth();
		int getDay();
		int getTerm();
		void setBorrow(int b);
		void setYear(int y);
		void setMonth(int m);
		void setDay(int d);
		int borrow(int n_y, int n_m, int n_d);
		void giveBack();
		int getTimeLimit();
		
		int getRoom();
		int getRoom_num();
		int getSeat();
		int getSeat_num();
		int getRoom_Time();
		int getSeat_Time();
		void Borrow(string Space_type, int Space_number, int return_time);
		int Return(string Space_type, int Space_number);
		int Empty();
		int Comeback();
};

class undergraduate : public member
{
	public :
		undergraduate(string rn, string T) : member(rn, T){
			canBorrow = 1;
			term = 13;
			seat_time_limit = 3;
		}
};

#endif
