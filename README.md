# System Software Experiment 3
## Project 1: Library Management
### Profect dexcription
 This program reads the `resource.dat` and `input.dat` and `space.dat` files from the library class and processes them according to the order of the input and generates output.
The main function only generated the library and the function that generates the library reads the file and stores and processes the data.
First, read the file `resource.dat` and save the contents of the data to the Vector declared as resource data type.
Read the `input.dat` file and `space.dat` file to store the vector declared as the member data type and process the input order using the information of each vector.

Getting started
-----
### What things you need to install and how to install
Among the files to run the program, we need `main.cpp`, `library.cpp`, `resource.cpp`, `member.cpp`.
Required data files include `resource.dat` and `input.dat`.
### How to compile
You can compile in two ways. The first method is as follows.
```
$ g++ -std=c++11 -o start main.cpp library.cpp resource.cpp member.cpp space.cpp
```
Other methods can be made through `Makefile`.
```
$ make
```
The above command creates an executable file called `start`.

Running
-----------
### Explain how to run
When a file named `start` is created through a compilation,
```
$ ./start >output.dat
```
You can obtain a result of `output.dat` through the command.

API
--------
### main.cpp
```
int main(){
	library *lab = new library();
	return 0;
}
```
The main function declares only library class.


### library.h
```
class library
{
	private:
		vector<resource*> RESLIST;
		vector<member*> MEMLIST;
	public:
		library();
};
```
Declares a vector for storing `resorce*` and `member*` data.
Start the project by executing the function of `library()`

### rsource.h
#### resource class
```
class resource
{
	protected:
		string res_Name;
		string mem_Name;
		string Type;	// "book"
		int B_year;	// borrow year
		int B_month;	// borrow month
		int B_day;	// borrow day
		int R_year;	// return until year
		int R_month;	// return until month
		int R_day;	// return until day
		int exist;	// 0 is already borrowed, 1 is exist in library
	public:
		resource(string rn, string T);	//initialize
		string getName();
		string getType();
		int getB_year();
		int getB_month();
		int getB_day();
		int getR_year();
		int getR_month();
		int getR_day();
		int borrow(string mn, int B_y, int B_m, int B_d, int R_y, int R_m, int R_d);
		int giveBack(string mn, int N_y, int N_m, int N_d);
};
```
```
resource::resource(string rn, string T)
```
Creadte and initialize a resource of type `resource`

```
int resource::borrow(string mn, int B_y, int B_m, int B_d, int R_y, int R_m, int R_d)
```
- Return 0 when borrow is success.
- Return 1 when you already borrowed this `Type` at B_y/B_m/B_d
- Return 2 when other member already borrowed this `Type`

```
int resource::giveBack(string mn, int N_y, int N_m, int N_d)
```
- Return 0 when return is success.
- Return 1 when delayed return.
- Return 2 when you did not borrow this `Type`.

#### book class
```
class book : public resource
{
	public :
		book(string rn, string T) : resource(rn, T){}
};
```
The book class is inherited from the resource class.

### member.h
#### member class
```
class member
{
	protected:
		string mem_Name;
		string Type;
		int canBorrow;	// you can borrow # of resource
		int nowBorrow;	// you borrow # of resource
		int ban_year;	// you can borrow after ban_year
		int ban_month;	// you can borrow after ban_month
		int ban_day;	// you can borrow after ban_day
		int term;		

		int seat_time_limit;
		int room;	// already borrowed 1, no borrowed 0
		int room_num;
		int seat;	// already borrowd 1, no borrowed 0
		int seat_num;
		int room_time;
		int seat_time;
		int empty_time;
	public:
		member(string mn, string T);	//initialize
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

		int getRoom();
		int getRoom_num();
		int getSeat();
		int getSeat_num();
		int getRoom_Time();
		int getSeat_Time();
		void Borrow(string Space_type, int Space_number, int return_time);
		void Return(string Space_type);
		void Empty(string Space_type, int hour);
		void Comeback(string Spce_type);
		void Reset();
};
```

```
member::member(string mn, string T)
```
Create and initialize a member of type `member`

```
int member::borrow(int n_y, int n_m, int n_d)
```
- Return 0 when you can borrow something.
- Return 1 when you are restricted member until ban_year/ban_month/ban_day
- Return 2 when exceeds your possible number of borrow.

```
void member::giveBack()
{
	nowBorrow--;
}
```
This function is called when the giveback something is successful.
Reduce `nowBorrow` by one as shown above.

```
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
```
This function is a function that is called when you try to borrow a space, and that is success.
Store "where space and when" in member information.

```
void member::Return(string Space_type)
{
	if(Space_type=="StudyRoom"){
		room = 0;
		room_num=0;
		room_time=0;
	}
	else if(Space_type=="Seat"){
		seat = 0;
		seat_num=0;
	}

}
```
This function is a function that is called when you try to return a spcae, and that is success.
Initialize information.

```
void member::Empty(string Space_type, int hour)
{
	empty_time = seat_time;
	seat_time = hour+1;
}
```
This function is a function that is called when you try to empty a spcae, and that is success.
Save seat_time(end of time) to empty_time and set seat_time hour+1.

```
void member::Comeback(string Space_type)
{
	seat_time = empty_time;
	empty_time = 0;
}
```
This function is a function that is called when you try to comeback at spcae, and that is success.
Return what you did in Empty function.


#### undergraduate class
```
class undergraduate : public member
{
	public :
		undergraduate(string rn, string T) : member(rn, T){
			canBorrow = 1;
			term = 13;
		}
};
```
The undergraduate class is inherited from the member class.

### space.h
#### space class
```
class space
{
	protected:
		int start_Time;
		int end_Time;
		int return_Time;
		int max_Num;
		
	public:
		space();
		int getST();
		int getET();
		int getRT();
		int Borrow(string memName, int hour, int nom, int time, int lilmit);
		int Return(string memName, int hour);
		void reset();
}			
```

```
space::space()
```
Create and initialize a space of type `space`

```
int space::Borrow(string memName, int hour, int nom, int time, int lilmit)
```
- if borrow is successful, store information of space and member.
- return Op code to library class.
- library class get Op code and print it.

```
int space::Return(string memName, int hour)
```
- if return is successful, initialize the space.
- return Op code to library class.
- library class get Op code and print it.

```
void space::reset()
```
- intialize at 24 o'clock.


#### study_room class
```
class study_room : public space
{
	protected:
		string user;

	public :
		study_room() : space(){
			start_Time = 9;
			end_Time = 18;
			return_Time = 0;
			max_Num=6;
			user="0";
		}
		void reset();
		int Borrow(string memName, int hour, int nom, int time, int lilmit);
		int Return(string memName, int hour);
		
};
```
The study_room class is inherited from the space class.

#### seat class
```
class seat : public space
{
	protected:
		int remain;	// maximum 50 seats
		string memname[50];
		int endtime[50];
		int emptytime[50];

	public :
		seat() : space(){
			start_Time = 0;
			end_Time = 24;
			remain = 0;
			max_Num=1;
			for(int i=0;i<50;i++){
				memname[i] = "0";
			}
			for(int i=0;i<50;i++){
				endtime[i]=0;
			}
			for(int i=0;i<50;i++){
				emptytime[i]=0;
			}	
		}
		void time_limit(int st, int et);
		int Borrow(string memName, int hour, int nom, int time, int lilmit);
		int Return(string memName, int hour);
		int Empty(string memName, int hour);
		int Comeback(string memName, int hour);
		void reset();
};

```
The seat class is inherited from the space class.

```
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
```
- This function is implemented when a member tries to leave his or her post.
- if empty is successful, store endtime to emptytime and switch endtime to hour+1.

```
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
```
- This function is implemented when a member tries to comeback.
- if comeback is successful, restore when you did at the Empty function.

Author
--------------
JuneKyu Park, Sungkyunkwan Univ., Semiconductor System Engeering.
