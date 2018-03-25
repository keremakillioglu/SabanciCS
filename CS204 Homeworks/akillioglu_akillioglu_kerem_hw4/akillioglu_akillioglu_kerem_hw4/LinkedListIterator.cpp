#include <iostream>
#include "linkedlistiterator.h"
using namespace std;

//default constructor
LinkedList::LinkedList()
{
	head = NULL;
	size = 0;
}

//Copy constructor for shallow copy.
//Don't use this. Use the deep copy version below.
/*LinkedList::LinkedList (const LinkedList & copy)
{
	head = copy.head;
	size = copy.size;
}*/


//Copy constructor for deep copy
LinkedList::LinkedList(const LinkedList & copy)
{
	head = copy.createClone();
	size = copy.size;
}

//destructor function visits all nodes and returns to heap
LinkedList::~LinkedList()
{
	node * ptr = head;
	while (ptr != NULL) {
		node * temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

void LinkedList::addToBeginning(int n)
{
	node *ptr = new node(n, head);
	head = ptr;
	size++;
}

void LinkedList::addToEnd(int n)
{
	node *created = new node(n, nullptr);
	node *ptr = head;

	while (ptr->next != nullptr)
	{
		ptr = ptr->next;
	}

	ptr->next = created;
	size++;
}

void LinkedList::printList() const
{
	node * ptr = head;
	while (ptr != nullptr) {
		cout << ptr->info << " ";
		ptr = ptr->next;
	}
	//cout << "size = " << size << endl << endl; This line is not wanted in the homework description
}


const LinkedList & LinkedList::operator+(const LinkedList & rhs)  //  this part is written to calculate the addition of two vectors
{
	node * ptr = rhs.head; // a clone of rhs's head pointer is created
	node * h1 = head; // a clone of our linked list's head is created
	if (size == rhs.length()) // if vectors length are equal
	{
		while (h1 != nullptr) //we move until the end of head pointer's clone
		{
			h1->info += ptr->info; // values at info part are summed up
			h1 = h1->next;
			ptr = ptr->next; // also we move one node from right hand side to stay on the right track
		}
	}

	return *this; //current value is returned 
}
//very similiar logic will be applied for the rest
const LinkedList & LinkedList::operator*(const LinkedList & rhs)  //  this part is written to calculate the multiplication of two vectors
{
	node * ptr = rhs.head;
	node * h1 = head;
	if (size == rhs.length())
	{
		while (h1 != nullptr) //we move until the end of head pointer's clone
		{
			h1->info *= ptr->info; // values at info part are multiplied
			h1 = h1->next;
			ptr = ptr->next;
		}
	}

	return *this;
}

const LinkedList & LinkedList::operator +(const int & rhs) //  this part is written to calculate the summation of a vector and an integer
{
	node * h1 = head;

	while (h1 != nullptr)
	{
		h1->info += rhs;  // values at info part are summed up with the integer
		h1 = h1->next;
	}

return *this;
}

const LinkedList & LinkedList::operator*(const int & rhs) // this part is written to calculate the multiplication of a vector and an integer
{
	node * h1 = head;

	while (h1 != nullptr)
	{
		h1->info *= rhs; // values at info part are multiplied with the integer
		h1 = h1->next;
	}

	return *this;
}

const int & LinkedList::operator%(const LinkedList & rhs) // this part is written to calculate the Dot product of two vectors (list1 % list2)
{
	node * ptr = rhs.head;
	node * h1 = head;
	int totalsum = 0; // totalsum refers to the sum of dot product, and it is initialized here

	if (size == rhs.length()) 
	{
		while (h1 != nullptr) //we move until the end of head pointer's clone
		{
			totalsum = totalsum + h1->info * ptr->info; // totalsum is updated here. First, the info values at both linked lists are multiplied. Then added to totalsum
			h1 = h1->next;
			ptr = ptr->next;
		}
	}
	return totalsum; // dot product is returned
}

void LinkedList::deleteList()
{
	node * ptr = head;
	while (ptr != NULL)
	{
		node * temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
	head = NULL;
	size = 0;
}

int LinkedList::length() const
{
	return size;
}

const LinkedList & LinkedList::operator = (const LinkedList & rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	if (this != &rhs)
	{
		deleteList(); // same as this->deleteList()
		head = rhs.createClone();
		size = rhs.size;
	}
	return *this;
}

//generates a clone of the linked list object by generating new copies of
//each node and connecting them as in the original.
//Returns the head of the clone list.
node * LinkedList::createClone() const
{
	if (head == NULL)  //if list is empty
		return NULL;   //clone is empty as well

	//first generate the first clone node and connect to head of clone
	node * headClone = new node(head->info, NULL);
	node * ptr = head->next;  //second node in orig.
	node * ptrClone = headClone; //to track the clone list
	while (ptr != NULL)
	{
		ptrClone->next = new node(ptr->info, NULL);
		ptr = ptr->next;
		ptrClone = ptrClone->next;
	}
	return headClone;
}


