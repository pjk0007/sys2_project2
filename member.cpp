#include <iostream>
#include <string>
#include "member.h"
using namespace std;

member::member(string mn, string T)
{
	mem_Name = mn;
	Type = T;
	nowBorrow = 0;
	ban_year=0;
	ban_month=0;
	ban_day=0;
	room = 0;
	seat = 0;
	room_num = 0;
	seat_num=0;
	seat_time=0;
	room_time=0;
}

string member::getName()
{
	return mem_Name;
}

int member::getBorrow()
{
	return nowBorrow;
}

int member::getYear()
{
	return ban_year;
}

int member::getMonth()
{
	return ban_month;
}

int member::getDay()
{
	return ban_day;
}

int member::getTerm()
{
	return term;
}

void member::setBorrow(int b)
{
	nowBorrow = b;
}


void member::setYear(int y)
{
	ban_year = y;
}

void member::setMonth(int m)
{
	ban_month = m;
}

void member::setDay(int d)
{
	ban_day = d;
}

int member::getRoom()
{
	return room;//0:not borrow, 1:already borrow
}

int member::getSeat()
{
	return seat;//0:not borrow, 1:already borrow
}

int member::borrow(int n_y, int n_m, int n_d)
{
	if(ban_year*360+ban_month*30+ban_day >= n_y*360+n_m*30+n_d){
		return 1;	// Restricted member untill ban_year/ban_month_ban_day
	}
	else if(canBorrow <= nowBorrow){
		return 2;	// Exceeds your possible number of borrow. Possible# of borrows : canBorrow
	}
	else {
		return 0;	// success
	}
}

void member::giveBack()
{
	nowBorrow--;
}

int member::getTimeLimit(){
	return seat_time_limit;
}

int member::getRoom_Time(){
	return room_time;
}
int member::getSeat_Time(){
	return seat_time;
}

void member::Reset()
{
	room=0;
	seat=0;
	room_num=0;
	seat_num=0;
	room_time=0;
	seat_time=0;
}

void member::Borrow(string Space_type, int Space_number, int return_time)
{
	if(Space_type=="StudyRoom"){
		room = 1;
		room_num=Space_number;
		room_time=return_time;
	}
	else if(Space_type=="Seat"){
		seat = 1;
		seat_num=Space_number;
		seat_time=return_time;
	}
}
