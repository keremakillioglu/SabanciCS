/*The aim of this program is taking source and search string inputs from the user. The search engine aims to search strings in source strings
through using string class functions. With respect to search operators, different search operations take place. According to the search rules,
program gives different outputs at different search operators.*/
//Kerem Akillioglu 24179
#include <iostream> //necessary libraries are added
#include <string>

using namespace std;// this line is used since standard namespace is used

void yahoo (string finalsource, string searcher) //this is my search engine and it will search the searcher inside my final source
{
	string wanted= searcher.substr(0,searcher.length()-1); // wanted string refers to the searcer string without a punctuation
	int initialpoint=0; //this is my initial point and will be updated in the following lines
	int spacex= finalsource.find(" "); // spacex integer is equal to the number at first space at the user's input string 

	while (spacex>0) // while this funtion finds a space in the user's given string, loop will continue to opearte 
	{
		string minisource = finalsource.substr(initialpoint,spacex-initialpoint); // this minisource ables me to divide my source string into single words
		//when my main source is seperated, function searches the "wanted" string in the main source's seperate words
		if (searcher[searcher.length()-1] == '*') // if searcher ends with '*' character, required actions will be taken to search string
		{
			int num= minisource.find(wanted); //num = the location of the searched string, inside the source string's divided part
			while (minisource.find(wanted,num) != string ::npos ) // if search string exists in the source string, loop will be activated
			{
			cout<<"index: "<<num+initialpoint<<" word: "<< minisource<< endl; //the current location in the seperated string is added to previous number of characters and summation gives the index
			//paramaters will be updated for the loop in the following lines:
			if(minisource.find(wanted,num+1)!= string::npos) //if one more search string exists in the seperated source string if statement will be realized
				num=num+minisource.find(wanted,num+1);	//num is updated as the summation of num itself and the location of the search string at the main string
			else
				num=num+1; //if there is no more search string in the seperated source string, num is added up by one and updated
			}
		}

		else if (searcher[searcher.length()-1] == '.') // if searcher ends with '.' character, required actions will be taken for search string
		{
			int b = minisource.length(); //length of the divided part of the mainsource is equal to b
			int c = wanted.length();  //length of the "wanted" string is equal to c
			int a = minisource.find(wanted,b-c); // a gives the location of wanted string while starting to search from b-c
			if (minisource.find(wanted,b-c) != string :: npos ) // since '.' operator asks only to search for the words that end with search string, an if statement can be used, a loop is not necessary for this case
			{ // if there is a search string in the asked location, it will be printed out 
				cout<<"index: "<<a+initialpoint<<" word: "<< minisource<< endl; // and the location of the search string is printed out as index point
			}
		}

		else if (searcher[searcher.length()-1] == '+') // if searcher ends with '+' character, required actions will be taken to search string
		{
			int b = minisource.length(); //length of the divided part of the mainsource is equal to b
			int c = wanted.length(); //length of the "wanted" string is equal to c
			int diff= b-c;// diff refers to difference between b and c
			int x = minisource.rfind(wanted,diff); // x is the operation to search wanted string inside the divided source REVERSELY string from starting from the point which is equal to difference of b and c
			int y = minisource.find(wanted,diff); //y is the operation to search wanted string inside the divided source string from starting from the point which is equal to difference of b and c

			if ( minisource.substr(0,wanted.length()) == wanted) //divided source is subdivided again. this part is the initial part of the string. if this subdivided substring is equal to searched string if statement will be realized
			{
				cout<<"index: "<<x+initialpoint<<" word: "<< minisource<< endl; // if there is a search string in the asked location, it will be printed out 
			}// the location of the search string is printed out as index point

			if (minisource.length() > wanted.length() && minisource.substr(minisource.length()- wanted.length()) == wanted) //divided source is subdivided again. this part is the end part of the string. if this subdivided substring is equal to searched string and the searched string is smaller than the divided substring in terms of length, if statement will be realized
			{	
				cout<<"index: "<<y+initialpoint<<" word: "<< minisource<< endl; // if there is a search string in the asked location, it will be printed out
			}// the location of the search string is printed out as index point
		}
		//these are the updates for my main loop:
		initialpoint=spacex+1; //initial point starts from zero and updated as the next space as loop keeps working.
		spacex=finalsource.find(" ",initialpoint); // location of the space is updated as the next space
	}
}

int main() // this is my main, and needed functions will be called in the following order
{
	string searcher, source, finalsource; // needed strings are defined 
	cout << "Enter source string: "; // a source input is asked from the user
	cin>> source; //user's initial input is stored as " source"

	while ( source!= "end" && source != "END" ) // if user's last word is not end or not END, this loop will take more inputs and it will not end unless the last word is "end" or "END"
	{
		finalsource= finalsource + source+" " ; //finalsource adds up all written inputs after plugging a space in between two inputs
		cin >> source; // input from user asked again
	}

	cout << "Enter search string: "; // program asks user to plug a search input
	cin>> searcher; // input is stored as searcher

	while (  searcher != "quit" && searcher != "QUIT"  ) // a control loop  is created. If searcher does not end with quit loop will continue to operate
	{										// if search input is not in the asked format, a loop will be created 
		yahoo (finalsource,searcher); //yahoo function is my search engine, we will plug the final source, and search the "searcher" string inside the final source. At the end, we will reach an asked format for source and search string
		cout << "Enter search string: "; //this loops asks user to plug an input and will not stop unless it is in the asked format
		cin >> searcher; // every input will be replaced if the previous one is at the asked format	    
	}

cin.ignore(); // These lines are written since I don't want my program to close itself
cin.get();
return 0; // this line provides me to run my program successfully
}