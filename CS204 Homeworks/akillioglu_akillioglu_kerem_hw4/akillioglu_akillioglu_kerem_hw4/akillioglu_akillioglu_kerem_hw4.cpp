//KEREM AKILLIOGLU, 24179
//This program aims to operate mathematical functions for mathematical vectors. 
//Overload operators are used to define these mathematical calculations: summation and multiplication of two vectors, summation and multiplication of one vector and one number
#include <iostream>
#include <string>
#include "LinkedListIterator.h"
#include <fstream>  //necessary libraries are added
using namespace std; //standard namespace is used

int main()
{
	LinkedList vector1, vector2; // required link list object variables are created
	int x1, x2, y1, y2; //x represents transactionid and y represents outputlocation
	int counter1 = 0;	int counter2 = 0; // counter variables are created to be used in the following loops

	cout << "Enter the first vector :" << endl;
	while (cin >> x2 && x2 != 35) // 35 is ASCII code for the char '#'
	{
		if (counter1 == 0) // a counter value is set to push to beggining if it is equal to '0' and return a length value
		{
			vector1.addToBeginning(x2); // first input is added to beginning
			counter1++;
		}
		else
		{
			vector1.addToEnd(x2); counter1++; // other inputs are added to the end
		}
	}
	cin.clear(); cin.ignore(); cin.get(); // these statements ables cin operator to take input again

	cout << "Enter the second vector :" << endl;// same operations held with the above
	while (cin >> y2 && y2 != 35) // 35 is ASCII code for the char '#'
	{
		if (counter2 == 0)
		{
			vector2.addToBeginning(y2);
			counter2++;
		}
		else
		{
			vector2.addToEnd(y2); counter2++;
		}
	}
	cin.clear(); cin.ignore(); cin.get(); // first input is added to beginning

	cout << "content of list1:" << endl; //contents of the mathematical vectors are printed
	vector1.printList(); cout << endl;
	cout << "content of list2:" << endl;
	vector2.printList();  cout << endl;
	//////////////////////////////////////////// 
	cout << "Calculating list1+list2 ..." << endl; // sum of two lists are calculated

	if (counter1 == counter2) // if lengths of these vectors are equal
		vector1 = vector1 + vector2; // their sum is calculated

	else
		cout << "ERROR: Lengths should be same!" << endl; // else an error message is displayed

	cout << "content of list1 after list1 + list2:" << endl; // list 1 and list2 values are printed seperately
	vector1.printList(); cout << endl;
	cout << "content of list2 after list1 + list2:" << endl;
	vector2.printList();  cout << endl;
	////////////////////////////////////////////

	cout << "Calculating list1*list2 ..." << endl; // with almost same logic with the above

	if (counter1 == counter2)
	{
		vector1 = vector1 * vector2; //two vectors are multiplied
	}
	else
	{
		cout << "ERROR: Lengths should be same!" << endl;
	}

	cout << "content of list1 after list1 * list2:" << endl;
	vector1.printList(); cout << endl;
	cout << "content of list2 after list1 * list2:" << endl;
	vector2.printList();  cout << endl;
	////////////////////////////////////////////
	cout << "Calculating list2+2 ..." << endl;
	cout << "content of list2 after list2+2:" << endl;  //a vector and a number are summed up
	vector2 = vector2 + 2; 	vector2.printList();  cout << endl;

	cout << "Calculating list2*4 ..." << endl;
	cout << "content of list2 after list2*4:" << endl; //a vector and a number are multiplieds
	vector2 = vector2 *4; 	vector2.printList();  cout << endl;
	////////////////////////////////////////////

	cout << "Calculating list1 % list2 ..." << endl; // dot product of two vectors are calculated 
	if (counter1 != counter2)
	{
		cout << "ERROR: Lengths should be same!" << endl;
	}

	cout << "Dot product of list1 and list2: ";

	if (counter1 == counter2)
	{
		int s = 0;	s = vector1 % vector2; cout << s;
	}
	else
	{
		cout << 0 << endl;
	}

	cin.get(); //these lines are added to prevent the program to close itself suddenly
	cin.ignore();
	return 0;
}