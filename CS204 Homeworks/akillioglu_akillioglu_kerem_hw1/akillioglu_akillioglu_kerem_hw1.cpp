//KEREM AKILLIOGLU, 24179
// This program aims to read input files and search words in sprial format as that user plugs the name of the file. 
// This file contains a matrix of characters and words to be searched in the clockwise spiral form.
// The input file is checked, if format is correct and searched words exist in the matrix in the clockwise spiral form, they are printed out. If file format is wrong, an error message is displayed.

#include <iostream>
#include <vector>
#include <string>
#include <sstream> //necessary libraries are added
#include <fstream>
#include "strutils.h"

using namespace std; // standard namespace is used

void getfilename(ifstream & reader, string & filename) //this function asks filename to user
{
	cout << "Enter the name of the file " << endl;
	cin >> filename;  // user plugs the name of the file
	reader.open(filename.c_str()); // it is tried to be opened
	while (reader.fail()) // if the file cannot be opened
	{
		cout << "Could not open the file " << filename << endl; // error message is displayed
		cout << "Enter the name of the file name" << endl; //The name of the file is asked to the user again
		cin >> filename;

		reader.open(filename.c_str()); //until file is opended successfully
	}
}

bool IsInt(string & taken, int & firstnumber, bool & check) // this function checks if the input is integer or not
{
	for (int i = 0; i < taken.length(); i++) // taken input string is checked char by char. 
	{
		if (!(taken.at(i) >= '0' && taken.at(i) <= '9')) //If every char does not correspond to a value between '0' and '9'
		{
			check = false; //then it means the taken input is not an integer
		}
		firstnumber = atoi(taken); // if taken input is an integer, then string format can be transformed to integer, and the value for the first number is set
		return check; // bool value is returned
	}
}


bool CheckLines(string & taken, int & firstnumber, bool & control) // length and chars inside of the lines will be checked
{
	string error = "Error: Input file is not in correct format!"; //an error message is created

	if (taken.length() != firstnumber) // if the length is not equal to the number plugged
	{
		cout << error << endl; // print out the error message
		control = false; //and return 
		return false;
	}

	for (int x = 0; x < taken.length(); x++) //this loop continues until it reaches taken word's end
	{
		if (!(taken.at(x) >= 'A' && taken.at(x) <= 'Z')) // if the word contains a letter different than capital letters
		{
			cout << error << endl;
			control = false; // it makes bool false
			return false; // and returns false
		}
	}

	return control; // if bool "control " is true at the end
}

void increment(int & cnt, int & move) // this function allows numbers to increment +1 in two rounds
{
	if (move % 2 == 0)
		move++;
	cnt++;
}

bool CheckandMove(bool & match, int & direction, int & a, int &b, int & cnt, int & move, int & firstnumber, string & word, vector < vector <char>> & matrix)
{
	int len = word.length() - 1;
	while (len > 0) // a loop should end when end of the word is reached. since letters 0 is already checked and known that letter 1 is at the upper side; movement should start from up
	{
		if (len > 0 && direction % 4 == 0) //	UP if the second letter exists in the upper side, movement should be like this : up,right ,down(x2), left (x2) and so on
		{
			increment(cnt, move); // movement is incremented

			for (int i = 0; i < move && len > 0; i++) // at the first two movements go 1, second two movements go 2 and so on
			{
				if ((a > 0) && (a < firstnumber) && (b >= 0) && (b < firstnumber)) // added for checking if the vector boundaries are exceeded or not
				{
					word.at(i) == matrix[a - 1][b]; // check the char at the upper side
				}

				else
					match = false; //if program does not found a match than it makes this bool value false
				len--; // decrease length as much as the cursor moves
			}
			cnt++; // counter is increased the control the number of moves
			direction++; // direction value is increased by one and movement is directed to the following direction
		}

		if (len > 0 && direction % 4 == 1) //  Same operation as UP is held with the direction RIGHT
		{
			increment(cnt, move);

			for (int i = 0; i < move && len > 0; i++) // at the first two movements go 1, second two movements go 2 and so on
			{
				if ((a >= 0) && (a < firstnumber) && (b >= 0) && (b + 1 < firstnumber)) // added for checking if the vector boundaries are exceeded or not
				{
					word.at(i) == matrix[a][b + 1];
				}

				else
					match = false;
				len--;
			}
			cnt++;
			direction++;
		}

		if (len > 0 && direction % 4 == 2) // //  Same operation as UP is held with the direction DOWN
		{
			increment(cnt, move);

			for (int i = 0; i < move && len > 0; i++) // at the first two movements go 1, second two movements go 2 and so on
			{
				if ((a >= 0) && (a + 1 < firstnumber) && (b >= 0) && (b < firstnumber)) // added for checking if the vector boundaries are exceeded or not
				{
					word.at(i) == matrix[a + 1][b];
				}

				else
					match = false;
				len--;
			}
			cnt++;
			direction++;
		}

		if (len > 0 && direction % 4 == 3) // //  Same operation as UP is held with the direction  LEFT
		{
			increment(cnt, move);

			for (int i = 0; i < move && len > 0; i++) // at the first two movements go 1, second two movements go 2 and so on
			{
				if ((a >= 0) && (a < firstnumber) && (b > 0) && (b < firstnumber)) // added for checking if the vector boundaries are exceeded or not
				{
					word.at(i) == matrix[a][b - 1];
				}

				else
					match = false;
				len--;
			}
			cnt++;
			direction++;
		}
	}

	return match;
}

int main()
{
	ifstream reader; //input file stream variables are created to read input from the files
	string filename, line1, line2, part1, part2;
	string taken;
	bool check = true;
	bool check2 = true;
	bool control = true;
	bool takeinput = true;// initialization is made for the following statements
	bool match = true;
	int firstnumber = 0;
	int secondnumber = 0;
	int direction; // an integer is set to define directions with numbers later on

	getfilename(reader, line1); // the name of the file is asked from the user
	getline(reader, line1); // first line is read and 
	IsInt(line1, firstnumber, check); // checked if the first input is an integer
	if (check == false)
		return false;

	vector < vector <char> > matrix; // a matrix is created
	vector < string > searched; // a vector for storing searched words are created

	int counter = 0; // a counter value has been set for the following loop
	while (takeinput && getline(reader, part1)) // lines will be picked until reaching the line number "counter"
	{
		vector <char> temp; // temporary vector is created
		CheckLines(part1, firstnumber, control); // lines are checked if they are in the correct format
		if (control == false)
			return false; // if not false value is returned

		for (int i = 0; i < part1.length(); i++)
		{
			temp.push_back(part1.at(i)); //characters in lines are stored in a temporary vector 
		}

		matrix.push_back(temp); //and this vector is added to the matrix vector
		counter++;
		if (counter == firstnumber)
			takeinput = false;
	}//when the loop finishes operating, matrix is created

	getline(reader, line2); // second part of the file is started to be read
	IsInt(line2, secondnumber, check2); // it is checked if the second part stars with an integer
	if (check2 == false)
		return false; // if not, program closes itself


	while (reader >> part2) // first line after the integer in the second part is read  
	{
		searched.push_back(part2); // and stored in an other vector
	}

	// SEARCH OPERATION BEGINS

	vector <string>  foundwords; // this vector stores the elements found after the search operation

	for (int i = 0; i < secondnumber; i++) // main loop will operate as much as the number of words that wanted to be searched
	{
		string word = searched[i]; // first searched word is defined as a string

		int a = 0;
		int b = 0; // initialization is made for the following statements
		int cnt = 0;
		int move = 0;

		bool f = false;
		for (a; a < firstnumber && !f; a++) // for a matrix[a][b] where a represents rows
		{
			for (b = 0; b < firstnumber && !f; b++)// b represent columns
			{
				if (word[0] == matrix[a][b]) // if first letter of the word matches with matrix
				{
					//check second letter of the word
					if ((a > 0) && (a < firstnumber) && (b > 0) && (b < firstnumber)) // if  a and b values are not at the borders of the matrix. otherwise vector will be exceeded and program will give error
					{
						if (a > 0 && word.at(1) == matrix[a - 1][b]) // If second letter matches with the word at the UPPER SIDE
						{
							direction = 0; // Assign direction 0 to UP
							CheckandMove(match, direction, a, b, cnt, move, firstnumber, word, matrix); //the spiral check function is called
							if (match == true) // if a match exists
							{
								f = true;
								foundwords.push_back(word);//found words are added to another vector
							}
						}

						else if (b < firstnumber - 1 && word.at(1) == matrix[a][b + 1]) // If second letter matches with the word at the RIGHT SIDE
						{
							direction = 1;// Assign direction 1 to RIGHT
							CheckandMove(match, direction, a, b, cnt, move, firstnumber, word, matrix); //  the same operation is held
							if (match == true)
							{
								f = true;
								foundwords.push_back(word);
							}
						}

						else if (a < firstnumber - 1 && word.at(1) == matrix[a + 1][b]) // If second letter matches with the word at the DOWN SIDE
						{
							direction = 2; // Assign direction 2 to DOWN
							CheckandMove(match, direction, a, b, cnt, move, firstnumber, word, matrix); //  the same operation is held
							if (match == true)
							{
								f = true;
								foundwords.push_back(word);
							}
						}

						else if (b > 0 && word.at(1) == matrix[a][b - 1]) // If second letter matches with the word at the LEFT SIDE
						{
							direction = 3; // Assign direction 3 to LEFT
							CheckandMove(match, direction, a, b, cnt, move, firstnumber, word, matrix);//  the same operation is held
							if (match == true)
							{
								f = true;
								foundwords.push_back(word);
							}
						}

						if (a == firstnumber) //these lines are added to make search operation safe and not exceed matrix's limits
							a = 0;
						if (b == firstnumber)
							b = 0;
					}
				}
			}
		}

	}

	if (foundwords.size() == 1) // in order to print words in the asked format 
		cout << foundwords.size() << " Word is Found: " << foundwords[0]; // if one word is found, it is printed with this statement

	if (foundwords.size() > 1)
	{
		string found; // found word members are collected in a string form
		for (int i = 0; i < foundwords.size(); i++)
		{

			found = found + " " + foundwords[i]; // and added one by one
		}

		cout << foundwords.size() << " Words are Found:" << found; //// if more than one words are found, they are printed with this statement
	}

	cin.ignore(); // these lines are added for preventing this program to close itself instantly
	cin.get();
	return 0;
}
