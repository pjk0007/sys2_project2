#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "library.h"
#include "member.h"
#include "resource.h"
#include "space.h"
using namespace std;


library::library()
{
	resource* tempRes;
	member* tempMem;
	study_room study_rooms[11];
	seat seats[4];
	seats[1].time_limit(0, 24);
	seats[2].time_limit(9, 21);
	seats[3].time_limit(9, 18);

	char input1[100], input2[100];
	char buf1[100], buf2[100], buf3[100], buf4[100];
	FILE* fp;
	FILE* fq;
	int year1, month1, day1, year2, month2, day2, hour;
	int date1, date2;
	int year, month, day, i;
	int cnt=1, exist=0;
	int b_year, b_month, b_day;
	string resName, resType, memName, memType;
	char BorR[3];

	int result;

	string Space_type;
	int Space_number;
	char Operation;
	int Number_of_member;
	int Time;
	int Op, Op_;
	int before_time;

	int file_end1=1, file_end2=1;
	int file_exist1, file_exist2;
	

	fp = fopen("resource.dat", "r");
	fscanf(fp, "%s", buf1);
	fscanf(fp, "%s", buf2);
	
	while(fscanf(fp, "%s", buf1)!=EOF)
	{
		resType = buf1;
		fscanf(fp, "%s", buf2);
		if(resType=="Book"){
			RESLIST.push_back(new book(buf2, buf1));
		}
	}
	fclose(fp);

	if(fp = fopen("input.dat", "r")){
		file_exist1=1;
		for(i=0;i<6;i++){
			fscanf(fp, "%s", buf1);
		}
	}
	else {
		file_end1=0;
		file_exist1=0;
	}

	if(fq = fopen("space1.dat", "r")){
		file_exist2=1;
		for(i=0;i<8;i++){
			fscanf(fq, "%s", buf3);
		}
	}
	else {
		file_end2=0;
		file_exist2=0;
	}

	cout << "Op_#	Return_code	Description"<<endl;
	while(1)
	{
		
		if(file_end1==1 && fscanf(fp, "%s", buf1)>0)
		{
			buf2[0]=buf1[0];
			buf2[1]=buf1[1];
			buf2[2]='\0';
			year1 = atoi(buf2);
			
			buf2[0]=buf1[3];
			buf2[1]=buf1[4];
			buf2[2]='\0';
			month1 = atoi(buf2);
			
			buf2[0]=buf1[6];
			buf2[1]=buf1[7];
			buf2[2]='\0';
			day1 = atoi(buf2);
		}
		else file_end1=0;
		if(file_end2==1 && fscanf(fq, "%s", buf3)>0)
		{
			buf4[0]=buf3[0];
			buf4[1]=buf3[1];
			buf4[2]=buf3[2];
			buf4[3]=buf3[3];
			buf4[4]='\0';
			year2 = atoi(buf4);
			
			buf4[0]=buf3[5];
			buf4[1]=buf3[6];
			buf4[2]='\0';
			month2 = atoi(buf4);
			
			buf4[0]=buf3[8];
			buf4[1]=buf3[9];
			buf4[2]='\0';
			day2 = atoi(buf4);

			buf4[0]=buf3[11];
			buf4[1]=buf3[12];
			buf4[2]='\0';
			hour = atoi(buf4);
		}
		else file_end2=0;

		date1 = year1*360+month1*12+day1;
		date2 = (year2%100)*360+month2*12+day2;

		if(file_end1<1 && file_end2<1) break;

		cout << cnt << "	";

		if((date1 <= date2 && file_end1>0) || file_end2<1){ 
			year = year1;
			month = month1;
			day = day1;
			if(date1 > before_time){
				for(int i=0;i<MEMLIST.size();i++){
					MEMLIST.at(i)->Reset();
				}
				for(int i=0;i<11;i++){
					study_rooms[i].reset();
				}
				for(int i=0;i<4;i++){
					seats[i].reset();
				}
			}
			before_time = year*360+month*12+day;
			if(file_end2>0) fseek(fq, -13, SEEK_CUR);

			fscanf(fp, "%s", buf1);
			fscanf(fp, "%s", buf2);
			resName = buf2;
			resType = buf1;
			exist = 0;
			for(i=0;i<RESLIST.size();i++){
				if(RESLIST.at(i)->getName() == resName){
					tempRes = RESLIST.at(i);
					exist++;
					break;
				}
			}
			fscanf(fp, "%s", BorR);
	
			fscanf(fp, "%s", buf1);
			fscanf(fp, "%s", buf2);
			memName = buf2;
			memType = buf1;
	
			if(MEMLIST.size()==0){
				if(memType=="Undergraduate"){
					MEMLIST.push_back(new undergraduate(buf2, buf1));
				}
				tempMem = MEMLIST.back();
			}
			else{
				for(i=0;i<MEMLIST.size();i++){
					if(MEMLIST.at(i)->getName() == memName){
						tempMem = MEMLIST.at(i);
						break;
					}
					else if(i==MEMLIST.size()-1){
						if(memType=="Undergraduate"){
							MEMLIST.push_back(new undergraduate(buf2, buf1));
						}
						tempMem = MEMLIST.back();
					}
				}
			}
	
			if(BorR[0]=='B'){
				if(exist==0){
					cout << "1	";	// return code 1
					cout << "Non exist resource." <<endl;
				}
				else if(tempMem->borrow(year, month, day)==2){
					cout << "2	";
					cout << "Exceeds your possible number of borrow. Possible # of borrows: ";
					cout << tempMem->getBorrow() << endl;
				}
				else if(tempMem->borrow(year, month, day)==0){
					b_year = (year*360+month*30+day + tempMem->getTerm()) / 360;
					b_month = ((year*360+month*30+day + tempMem->getTerm()) - b_year*360) / 30;
					b_day = ((year*360+month*30+day + tempMem->getTerm()) - b_year*360 - b_month*30);
					if(tempRes->borrow(tempMem->getName(), year, month, day, b_year, b_month, b_day)==1){
						cout << "4	";
						cout << "You already borrowed this ";
						cout << setw(2) << setfill('0') << tempRes->getB_year() <<"/";
						cout << setw(2) << setfill('0') << tempRes->getB_month() <<"/";
						cout << setw(2) << setfill('0') << tempRes->getB_day() << endl;
					}
					else if(tempRes->borrow(tempMem->getName(), year, month, day, b_year, b_month, b_day)==2){
						cout << "5	";
						cout << "Other member already borrowed this ";
						cout << tempRes->getType()<<". This " << tempRes->getType() <<" will be returned at ";
						cout << setw(2) << setfill('0') << tempRes->getR_year() <<"/";
						cout << setw(2) << setfill('0') << tempRes->getR_month()<<"/";
						cout << setw(2) << setfill('0') << tempRes->getR_day() <<endl;
					}
					else {
						tempMem->setBorrow(tempMem->getBorrow()+1);
						cout << "0	Success." <<endl;
					}
				
				}
				else if(tempMem->borrow(year, month, day)==1){
					cout << "6	";
					cout << "Restricted member until ";
					cout << setw(2) << setfill('0') << tempMem->getYear()<<"/";
					cout << setw(2) << setfill('0') << tempMem->getMonth()<<"/";
					cout << setw(2) << setfill('0') << tempMem->getDay()<<endl;
				}
			}
			else if(BorR[0]=='R'){
				if(tempRes->giveBack(tempMem->getName(), year, month, day) == 0){
					tempMem->giveBack();
					cout << "0	Success." <<endl;
				}
				else if(tempRes->giveBack(tempMem->getName(), year, month, day) == 2){
					cout << "3	You did not borrow this "<< tempRes->getType() <<"."<<endl;
				}
				else{
					result = year*360 + month*30 + day - tempRes->getR_year()*360 - tempRes->getR_month()*30 - tempRes->getR_day();
					b_year = (year*360+month*30+day + result) / 360;
					b_month = ((year*360+month*30+day + result) - b_year*360) / 30;
					b_day = ((year*360+month*30+day + result) - b_year*360 - b_month*30);
	
					tempMem->setYear(b_year);
					tempMem->setMonth(b_month);
					tempMem->setDay(b_day);
					tempMem->giveBack();
	
					cout << "7	Delayed return. You'll be restricted until ";
					cout << setw(2) << setfill('0') << tempMem->getYear() <<"/";	
					cout << setw(2) << setfill('0') << tempMem->getMonth() <<"/";	
					cout << setw(2) << setfill('0') << tempMem->getDay()<<endl;
				}
			}
		}
		else if((date1 > date2 && file_end2>0) || file_end1<1){ 
			year = year2;
			month = month2;
			day = day2;
			if(date2 > before_time){
				for(int i=0;i<MEMLIST.size();i++){
					MEMLIST.at(i)->Reset();
				}
				for(int i=0;i<11;i++){
					study_rooms[i].reset();
				}
				for(int i=0;i<4;i++){
					seats[i].reset();
				}
			}
			before_time = (year%100)*360+month*12+day;

			if(file_end1>0) fseek(fp, -8, SEEK_CUR);

			fscanf(fq, "%s", buf3);
			Space_type = buf3;
			fscanf(fq, "%s", buf3);
			Space_number = atoi(buf3);
			fscanf(fq, "%s", buf3);
			Operation = buf3[0];
			fscanf(fq, "%s", buf3);
			memType = buf3;
			fscanf(fq, "%s", buf4);
			memName = buf4;
			
			if(MEMLIST.size()==0){
				if(memType=="Undergraduate"){
					MEMLIST.push_back(new undergraduate(buf4, buf3));
				}
				tempMem = MEMLIST.back();
			}
			else{
				for(i=0;i<MEMLIST.size();i++){
					if(MEMLIST.at(i)->getName() == memName){
						tempMem = MEMLIST.at(i);
						break;
					}
					else if(i==MEMLIST.size()-1){
						if(memType=="Undergraduate"){
							MEMLIST.push_back(new undergraduate(buf4, buf3));
						}
						tempMem = MEMLIST.back();
					}
				}
			}

			if(Operation=='B'){
				fscanf(fq, "%s", buf3);
				Number_of_member = atoi(buf3);
				fscanf(fq, "%s", buf3);
				Time = atoi(buf3);
			}

			Op=0;
			Op_=0;

			int Op1, Op2;
			if(Operation=='B'){
				if(Space_type=="StudyRoom" && Space_number>=1 && Space_number<=10){
					if(tempMem->getRoom()==1 && tempMem->getRoom_Time()>hour) Op_=11;
					else Op=study_rooms[Space_number].Borrow(memName, hour, Number_of_member, Time, 3);
					if(Op==9){
						Op1 = study_rooms[Space_number].getST();
						Op2 = study_rooms[Space_number].getET();
					}
					else if(Op==14){
						Op1 = study_rooms[Space_number].getRT();
					}
				}
				else if(Space_type=="Seat" && Space_number>=1 && Space_number<=3){
					if(tempMem->getSeat()==1 && tempMem->getSeat_Time()>hour) Op_=11;
					else Op=seats[Space_number].Borrow(memName, hour, Number_of_member, Time, tempMem->getTimeLimit());
					if(Op==9){
						Op1 = seats[Space_number].getST();
						Op2 = seats[Space_number].getET();
					}
					else if(Op==14){
						Op1 = seats[Space_number].getRT();
					}
				}
				else Op=8;

				
				if(Op==8) cout<< "8	Invalid space id." << endl;
				else if(Op==9) {
					cout << "9	This space is not available now. Available from "; 
					cout << setw(2) << setfill('0') << Op1 << " to ";
					cout << setw(2) << setfill('0') << Op2 <<"."<<endl;	
				}
				else if(Op_==11) cout <<"11	You already borrowed this kind of space."<<endl;
				else if(Op==12) cout << "12	Exceed available number." <<endl;
				else if(Op==13) cout << "13	Exceed available time."<<endl;
				else if(Op==14) cout << "14	There is no remain space. This space is available after "<< Op1<<"."<<endl;
				else if(Op==0){
					tempMem->Borrow(Space_type, Space_number, hour+Time);
				       	cout << "0	Success." <<endl;
				}


			}
			else if(Operation=='R'){
				if(Space_type=="StudyRoom" && Space_number>=1 && Space_number<=10){
					Op=study_rooms[Space_number].Return(memName, hour);
					tempMem->Return(Space_type);
				}
				else if(Space_type=="Seat" && Space_number>=1 && Space_number<=3){
					Op=seats[Space_number].Return(memName, hour);
					tempMem->Return(Space_type);
				}
				else Op=8;

				if(Op==8) cout << "8	Invalid space id." <<endl;
				else if(Op==10) cout << "10	You did not borrow this space." << endl;
				else if(Op==0) cout << "0	Success." <<endl;
			}
			else if(Operation=='E'){
				if(Space_type=="Seat" && Space_number>=1 && Space_number<=3){
					Op=seats[Space_number].Empty(memName, hour);
					if(Op==0) tempMem->Empty(Space_type, hour);	
				}
				else Op=8;

				if(Op==8) cout << "8	Invalid space id." <<endl;
				else if(Op==10) cout << "10	You did not borrow this space." << endl;
				else if(Op==0) cout << "0	Success." <<endl;
			}
			else if(Operation=='C'){
				if(Space_type=="Seat" && Space_number>=1 && Space_number<=3){
					Op=seats[Space_number].Comeback(memName, hour);	
					if(Op==0) tempMem->Comeback(Space_type);	
				}
				else Op=8;

				if(Op==8) cout << "8	Invalid space id." <<endl;
				else if(Op==10) cout << "10	You did not borrow this space." << endl;
				else if(Op==0) cout << "0	Success." <<endl;
			}
		}

		cnt++;
	}
	if(file_exist1==1)
		fclose(fp);
	if(file_exist2==1)
		fclose(fq);
}
