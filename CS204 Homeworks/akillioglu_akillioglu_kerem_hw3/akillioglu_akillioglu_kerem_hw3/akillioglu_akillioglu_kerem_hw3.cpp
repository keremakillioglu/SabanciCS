//KEREM AKILLIOGLU, 24179
//This program aims to find a pathway out of the maze. An input file is read, inputs are stored in a matrix. 
//Then possible pathways are stored in a dynamic stack. If the pathway does not lead to maze's end, it is popped out. Otherwise the correct pathway is printed
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "dynintstack.h"
#include <fstream>  //necessary libraries are added
using namespace std; //standard namespace is used

void getfilename(ifstream & reader, string & filename) //this function asks filename to user
{
	cout << "Enter the input file name : " << endl;
	filename = "data3.txt";
	cin >> filename;  // user plugs the name of the file
	reader.open(filename.c_str()); // it is tried to be opened
}

void RecursiveReversePrint(DynIntStack s) //This function prints a stack in the reverse order
{
	if (s.isEmpty()) // if stack is empty function does nothing
		return;
	int a = s.top->xvalue; //x and y values of the stack's top are equilized to variables
	int b = s.top->yvalue;
	s.pop(a, b); // top of the stack is popped out
	RecursiveReversePrint(s); // function is called again
	cout << a << " " << b << endl; // a space is printed in between of these two numbers
}



int main()
{
	ifstream reader; string filename, lines, line1; //necessary variables are created to read the input file 
	getfilename(reader, filename);

	int rows, columns;

	getline(reader, line1); //first line is taken
	istringstream minireader(line1); // two numbers in the file are read
	minireader >> rows; minireader >> columns; // these integers are assigned as row and column numbers

	vector <vector <char> >  matrix; // a matrix is created to store 'X's and 'Y's in the file

	while (getline(reader, lines)) //Input file is read and inputs are stored in a matrix at this point
	{
		vector <char> temp;

		for (int i = 0; i < lines.length(); i++)
		{
			temp.push_back(lines[i]);
		}
		matrix.push_back(temp);
	}

	DynIntStack stack;  stack.push(0, 0); matrix[0][0] = 'V'; //Search Operation Begins After This Comment

	int x = 0; int y = 0; // x represents rows and y represents columns

	while (!(stack.isEmpty())) //this loop contiunes while the stack iis not empty
	{
		int curx = stack.top->xvalue; // current x and y values of the stack are assigned to variables
		int cury = stack.top->yvalue;
		stack.pop(curx, cury);

		if (x == rows - 1 && y == columns - 1) // if the end of loop is reached
		{
			stack.push(rows - 1, columns - 1); //last member of the maze is pushed to stack
			break; // and we get out of the loop
		}

		if (x + 1 >= 0 && y >= 0 && x + 1 < rows && y < columns && matrix[x + 1][y] == 'X') // this statement checks if i am in the matrix and 'X' exist in the down side 
		{
			matrix[x + 1][y] = 'V'; //almost the same operation is held with the statement in the above
			stack.push(curx, cury);
			stack.push(x + 1, y);
			x = x + 1;
		}

		else if (x >= 0 && y + 1 >= 0 && x < rows && y + 1 < columns && matrix[x][y + 1] == 'X') // this statement checks if i am in the matrix and 'X' exist in the right side 
		{
			matrix[x][y + 1] = 'V'; //change to content of the matrix to V, which marks that I visited that point
			stack.push(curx, cury); //previous points are pushed
			stack.push(x, y + 1); // since there exists an 'X' at this point, this point is pushed to matrþx
			y = y + 1; // y is updated
		}

		else if (x >= 0 && y - 1 >= 0 && x < rows && y - 1 < columns && matrix[x][y - 1] == 'X') // this statement checks if i am in the matrix and 'X' exist in the left side  
		{
			matrix[x][y - 1] = 'V'; //almost the same operation is held with the statement in the above
			stack.push(curx, cury);
			stack.push(x, y - 1);
			y = y - 1;
		}
		else if (x - 1 >= 0 && y >= 0 && x - 1 < rows && y < columns && matrix[x - 1][y] == 'X') // this statement checks if i am in the matrix and 'X' exist in the above
		{
			matrix[x - 1][y] = 'V'; //almost the same operation is held with the statement in the above
			stack.push(curx, cury);
			stack.push(x - 1, y);
			x = x - 1;
		}

		else //if 'X' is not found
		{
			if (stack.isEmpty()) //Firstly it is checked if the stack is empty
			{
				cout << "Solution NOT found!" << endl; //If the stack is empty at the end Error Message is displayed
				break; //and we get out of the loop
			}
			x = stack.top->xvalue; //if stack is not empty, we turn back to last points
			y = stack.top->yvalue;
		}

	}
	if (!(stack.isEmpty())) //if stack is not empty
		RecursiveReversePrint(stack); //correct pathway is printed

	cin.get(); //these lines are added to prevent the program to close itself suddenly
	cin.ignore();
	return 0;
}