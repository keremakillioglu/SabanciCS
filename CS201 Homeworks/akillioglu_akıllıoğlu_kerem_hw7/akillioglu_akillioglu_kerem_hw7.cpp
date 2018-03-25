//KEREM AKILLIOGLU, 24179
/*This program reads data from two separate input files. As director and movie names are read from the input files, movies will be sorted according to their ratings in a descending order. Later on, this program will print a text file as an output file while calculating and sorting movies’ average rating points. */
#include <iostream>
#include "strutils.h"
#include <vector>
#include <sstream>//necessary libraries are added
#include <fstream>
#include <string>
using namespace std;//standard namespace is used

struct movie // struct is created, as requested
{
	double rating ,numberofratings ; //since double type is needed rating and total number of ratings are created accordingly
	string  name ,director ;
};

void getfilename(ifstream & reader, string & datafile, string asked) // this function is used to receive filename from the user
{
	cout<< "Please enter a filename for "<<asked<<" file: "; //input from user is asked
	cin>> datafile; //user plugs a string value of datafile
	reader.open(datafile.c_str()); //asked file is opened
	while (reader.fail()) //if it input file stream fails to open
	{
		cout<< " Can not find the specified file."<<endl ;
		cout<< "Please enter a filename for "<<asked<<" file: "; //input from user is asked
		cin>> datafile;//program asks user to type a new file name
		reader.open(datafile.c_str()); //program opens the plugged datafile 
	}

}

void getdata(ifstream & reader,vector<movie> & vec ) // this function is used to receive rating, it gets rating
{
	string word,line;
	while(getline(reader,line))//data is read line by line
	{
		istringstream minireader(line); //an input string stream has been created
		int a = -1; // since compiler equalizes -1 as npos
		string  MovieName="";
		string directors="";
		while(a== string::npos) // this loop will take place until a is not equal to npos
		{
			minireader>>word; // input string stream will read word by word
			a= word.find(";"); // first ";" has been found
			directors+= word+ " "; // director name is updated
		}

		directors=directors.substr(0, directors.length()-2); // space and ';' is removed from the director name

		movie film; //struct created
		while (minireader>>word) //minireader reads rest of the line which is name, as reader continues to read; name value will be taken
		{
			ToUpper(word); //name is converted to capital letters
			MovieName += word + " "; // fullname is the sum of words while input string stream is able to read words
		}
		MovieName= MovieName.substr(0,MovieName.length()-1); // last space removed
		film.director = directors;
		film.rating = 0;
		film.numberofratings = 0; // members of the struct are initialized
		film.name = MovieName;
		vec.push_back(film); // struct is plugged to vector
	}
}


void getrating(ifstream & reader,vector<movie> & vec )  // this function is used to receive rating, it gets rating
{
	string line, word;
	int rate;

	while(getline(reader,line)) // while reading line by line
	{
		string MovieName = ""; // movie name is initialized
		istringstream minireader(line); //an input string stream has been created
		minireader>>word; // input string stream will read word by word
		double rate=atof(word);

		while (minireader>>word) //minireader reads rest of the line which is name, as reader continues to read; name value will be taken
		{
			ToUpper(word); //name is converted to capital letters
			MovieName += word + " "; // fullname is the sum of words while input string stream is able to read words
		}

		MovieName= MovieName.substr(0,MovieName.length()-1); // last space removed

		for(unsigned int i=0; i< vec.size() ; i++) // rating and number of plugged ratings are updated for every member of the given vector
			if(vec[i].name == MovieName)
			{
				vec[i].numberofratings ++;
				vec[i].rating+= rate;
			}
	}
}

void Sortie (vector<movie> & v1) // this function sorts vector's member integers in a descending order
{
	for(int i=0; i<v1.size() - 1; i++) //first member of the vector is compared
	{
		for(int j=i+1; j < v1.size(); j++) // with the rest of the vector's members
		{
			if ( v1[i].rating /v1[i].numberofratings < v1[j].rating / v1[j].numberofratings) //averages of the movies' ratings are compared
			{
				movie temp = v1[i]; //sorted in a descending order
				v1[i]= v1[j];
				v1[j]= temp;
			}

			else if ( v1[i].rating /v1[i].numberofratings == v1[j].rating / v1[j].numberofratings) // if averages of the movies' ratings are equal
			{

				if(v1[i].name>v1[j].name) // they will be sorted in an alphabetical order
				{	movie temp = v1[i];
					v1[i]= v1[j];
					v1[j]= temp;
				}	
			}
		}
	}
}


void Print (vector<movie> & v1) // this function is used to create out files
{
	string name;
	cout<< "Please enter a filename for output file: ";// output name is asked from the user
	cin>> name;
	ofstream PrintOut (name); // output file's name is created accordingly 
	PrintOut<< "RANK,NAME,DIRECTOR,POINTS"<< endl; // output is stated
	for (int a=0; a<v1.size(); a++)
	{
		PrintOut<< a+1 <<", "<< v1[a].name<< ", " << v1[a].director << ", " << v1[a].rating / v1[a].numberofratings << endl; 
		//members of the vector and average of the movies are printed in the requested format
	}
	cout<< "Results are in the file: "<<name<< endl;
}

int main () 
{
	string datafile,asked; //initialization 
	string directors="";
	ifstream reader1, reader2; //input file stream is created
	getfilename(reader1,datafile,"Movie-Director"); // file name is asked from the user
	getfilename(reader2,datafile,"Rating"); // file name is asked from the user
	vector<movie> database; // a vector is created
	getdata(reader1,database); // movie and director name is collected
	getrating (reader2,database); // rating is collected and matched with the movies 
	Sortie(database); // data is sorted
	Print(database); // data is printed

	cin.ignore(); // these lines are added for preventing this program to close itself instantly
	cin.get();
	return 0;
}