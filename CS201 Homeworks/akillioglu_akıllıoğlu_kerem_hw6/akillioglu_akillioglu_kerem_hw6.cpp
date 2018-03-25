//KEREM AKILLIOÐLU 24179
//This program takes 2 month and year values from the user, creates two date regarding the user's inputs. After these inputs have been created the comparison of dates in starts.
//If dates in text file are in between user's input dates, an output text file will be created. Regarding the records that include birth date, name and gender, inputs are been read. 
//If dates in text file are in between user's input dates, that person's records are printed in a text document regarding person's gender. 
#include <iostream> //necessary libraries are added
#include "strutils.h"
#include "date.h"
#include <fstream>
#include <sstream>
using namespace std; //standard namespace is used

bool IsInt(string s) // this bool function checks whether input is integer or not
{
	bool check = true; //inital bool value is true
	for (unsigned int i = 0 ; i < s.length() && check;i ++)
		if(s.at(i) < '0' || s.at(i) > '9') //if a character inside of this string is not an integer, 
			check = false; // bool value is changed to false
	return check; //this bool function returns check value
}
int TakeAndControlInput(int a, int b, string s1, string s2) //this function takes values from user and checks if the values fit the asked condition
{
	string tmp; // a temporary string has been created
	int c; //initialization
	bool inputcoming= true;
	while(inputcoming) // since bool condition is true, this loop will continue
	{
		cin >> tmp; //inputs are taken with cin operator
		if( IsInt(tmp) == true) //if taken input is true this if statement will realize
		{
			c = atoi(tmp); //since the input is a number, the input which is taken as string can be converted into integer
			if (!(c <= b && c >= a )) //if input is not in between of two values that user plugged
			{
				cout<< "Integer value must be between "<< a <<" and "<< b <<endl; //this error message will be displayed as asked
				cout<< "Please enter "<< s1 <<" value for "<< s2 <<" date: ";
			}
			else // it means that the plugged input is a fully number, and it is in the asked range
				inputcoming = false; // therefore there is no reason to continue this loop 
		}
		else //following statements mean that input is not fully a number
		{
			cout << "You have to enter an integer value. "<<tmp<<" is not an integer." << endl; //input is displayed and it is been said that input is not integer
			cout<< "Please enter "<< s1 <<" value for "<< s2 <<" date: "; //another value is asked from the user
		}
	}
	return c; // at the end c value is returned; as this function's return type is int
}
void GetData(string line, Date & d_f, string & gender, string & FullName ) // this function is used to take a data from the user
{
	istringstream minireader(line); //an input string stream has been created
	string word;
	minireader>>word; // input string stream will read word by word

	int a = word.find("/"); // first "/" has been found
	int numday = atoi(word.substr(0, a));// characters until first '/' represent the day
	int b = word.find("/",a+1); // second "/" has been found
	int nummonth = atoi(word.substr(a+1,b-a-1)); //month is created as the value between two '/' forms
	int numyear= atoi(word.substr(b+1));	//since the rest of the numbers form year, year is taken

	Date d (nummonth,numday,numyear); // with given values plugged, a date is created
	d_f = d;

	minireader>>gender; ToLower(gender); //gender letter is converted to lowercase letter

	while (minireader>>word) //minireader reads rest of the line which is name, as reader continues to read; name value will be taken
	{
		string a = word.substr(0,1); ToUpper(a); //only first letter of the input is uppercase
		string b = word.substr(1); ToLower (b); // rest of the input is lowercase
		word=a+b; //since input has been seperated early on, it is converged right now
		FullName += word + " "; // fullname is the sum of words while input string stream is able to read words
	}
}

void CreateOutFiles(Date date1, Date date2, ifstream & reader) // this function is used to create out files
{
	Date d; string gender, FullName;	//initialization 
	ofstream MaleOut ( "OutputMale_"+itoa(date1.Month())+"-"+ itoa(date1.Year())+"_"+itoa(date2.Month())+"-"+itoa(date2.Year())+".txt"); // output files' name are created accordingly to gender
	ofstream FemaleOut ( "OutputFemale_"+itoa(date1.Month())+"-"+ itoa(date1.Year())+"_"+itoa(date2.Month())+"-"+itoa(date2.Year())+".txt" ); //itoa is used to convert numbers into strings

	string line,word;
	while (getline(reader,line) )//getline is used to take values line by line
	{
		FullName = ""; //initialization
		GetData(line, d, gender, FullName ); // GetData function is called to receive datas
		if ( d >= date1 &&  d <= date2  ) //if the received data is in between the user created
		{
			if (gender=="m") //gender of the person is identified and data is created out to male file as asked
				MaleOut<< d.ToString() << " "<<  d.DayName() << " " << FullName << endl;

			else   //gender of the person is identified and data is created out to female file as asked
				FemaleOut<< d.ToString() << " "<<  d.DayName() << " " << FullName << endl;
		}
	}
}
int main()//birth date, gender and name 
{
	int month1, year1, month2, year2; //these integers are defined and it will created for user to plug some numbers
	string datafile;
	cout<< "Please enter the name of the data file: "; //input from user is asked
	cin>> datafile; //user plugs a string value of datafile
	ifstream reader; // an input file stream has been creared with name reader
	reader.open(datafile.c_str()); //asked file is opened
	while (reader.fail()) //if it input file stream fails to open
	{
		cout<< "You have entered wrong file name. Please enter the name of the data file: ";
		cin>> datafile;//program asks user to type a new file name
		reader.open(datafile.c_str()); //program opens the plugged datafile 
	}

	cout<< "Please enter month value for first date: "; //input from user is asked
	month1= TakeAndControlInput(1,12,"month", "first"); //first value of month is asked
	cout<< "Please enter year value for first date: ";
	year1=TakeAndControlInput(1900,2100,"year","first"); //first value of year is asked
	Date date1 (month1,1,year1); //first date is created

	cout<< "Please enter month value for second date: "; //it is almost identical with receiving first input and creating first date
	month2=TakeAndControlInput(1,12,"month","second"); 
	cout<< "Please enter year value for second date: ";
	year2=TakeAndControlInput(1900,2100,"year","second"); 
	Date date2 (month2,1,year2);

	int sYear=0, gYear=0, sMonth=0, gMonth=0; //these values have been initialized

	if(date1 > date2)//if date 1 is greater
	{
		Date tmp = date1;
		date1 = date2; //date 1 is equalized to date2 and date2 becomes the bigger date
		date2 = tmp; //smaller date is swapped with date1
	}//after this if condition and its process, date2 becomes the bigger date in all cases

	CreateOutFiles(date1, date2, reader);//this function creates output files

	cin.get(); // these lines are added for program to not close immidiately
	cin.ignore();
	return 0;
}