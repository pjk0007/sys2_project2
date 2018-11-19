#include <iostream>
#include <string>
#include "space.h"
using namespace std;

space::space()
{
	start_Time = 0;
	end_Time = 24;
}

int space::getST()
{
	return start_Time;
}

int space::getET()
{
	return end_Time;
}

int space::getRT()
{
	return return_Time;
}

void study_room::reset()
{
	return_Time = 0;
	user="0";
}

int study_room::Borrow(string memName, int hour, int nom, int time, int limit)
{
	if(hour < start_Time || hour > end_Time) return 9;
	if(nom>max_Num || nom<1) return 12;
	if(limit < time || time < 1) return 13;
	if(hour < return_Time) return 14;
	
	return_Time= hour+time;
	user = memName;

	return 0;
}

int study_room::Return(string memName, int hour)
{
	if(memName != user) return 10;
	if(hour >= return_Time) return 10;

	user = "0";
	return_Time=0;

	return 0;
}

void seat::reset()
{
	return_Time = 0;
	remain = 0;
	for(int i=0;i<50;i++){
		memname[i] = "0";
	}
	for(int i=0;i<50;i++){
		endtime[i] = 0;
	}
}

int seat::Borrow(string memName, int hour, int nom, int time, int limit)
{
	remain=0;
	for(int i=0;i<50;i++){
		if(endtime[i] <= hour) memname[i]="0";
	}
	for(int i=0;i<50;i++){
		if(memname[i]!="0") remain++;
	}

	if(hour < start_Time || hour > end_Time) return 9;
	if(nom>max_Num || nom<1) return 12;
	if(limit < time || time < 1) return 13;
	if(remain > 49) return 14;
	
	
	return_Time = hour+time;
	for(int i=0;i<50;i++){
		if(endtime[i]>hour && return_Time>endtime[i])
			return_Time = endtime[i];
	}

	for(int i=0;i<50;i++){
		if(memname[i]=="0"){
			memname[i]=memName;
			endtime[i]=hour+time;
			return 0;
		}
	}
}

int seat::Return(string memName, int hour)
{
	for(int i=0;i<50;i++){
		if(memname[i]==memName){
			if(hour < endtime[i]) return 0;
		}
	}

	return 10;

}

int seat::Empty(string memName, int hour)
{
	for(int i=0;i<50;i++){
		if(memname[i]==memName){
			if(hour <= endtime[i]){
				emptytime[i]=endtime[i];
				endtime[i]=hour+1;
			       	return 0;
			}
		}
	}
	return 10;
}

int seat::Comeback(string memName, int hour)
{
	for(int i=0;i<50;i++){
		if(memname[i]==memName){
			if(hour <= endtime[i]){
				endtime[i]=emptytime[i];
				emptytime[i]=0;
			       	return 0;
			}
		}
	}
	return 10;
}

void seat::time_limit(int st, int et){
	start_Time = st;
	end_Time = et;
}

