#include "robots.h"	//KEREM AKILLIOÐLU 24179
using namespace std;	//Necessary libraries added

bool isfirstsmallest(int x, int y, int z) //finds the smallest number, at my main function; it will help me to calculate shortest distance
{
	if (x<=y && (x<=z)) //if the first written variable is the smallest number bool returns true
	{return true;
	}

	else
	{return false;		//if the first written variable is not the smallest number bool returns false
	}
}

bool terminate (int a) // if user's input is smaller than 0, program will terminate itself
{
	if (a >= 0)
	{return true;}

	else 
	{ ShowMessage("The coordinate is entered as wrong and your program should come to the end");	//error message is shown
	return false;}	//the structure for terminating the program has been set
}

void turneast(Robot & sinan) // this function affects my created robot and it ables to make robot face east all the time
{
	while (! sinan.FacingEast() ) // loop created and if robot is not facing east
	{ 
		sinan.TurnRight();		// robot turns right until the robot faces east	
	}
}

void turn180(Robot & sinan)	//this function ables robot to turn 180 degrees
{
	sinan.TurnRight();
	sinan.TurnRight();
}

void turn270(Robot & sinan) //this function ables robot to turn 270 degrees
{
	sinan.TurnRight();
	sinan.TurnRight();
	sinan.TurnRight();
}

void turn90right(Robot & sinan) //this function ables robot to turn 90 degrees
{
	sinan.TurnRight();
}

void yallah (int x, int y, Robot & sinan) // these x and y values will refer to "user input-target" in the following
{											//yallah function provides my robot to move in x and y direction
	if (x>=0) //MOVEMENT IN X-DIRECTION. If the input's difference between target is positive these lines will be realized
	{	turneast(sinan);
		sinan.Move(abs(x));}

	else	//if the input's difference between target is negative these lines will be realized
	{	turneast(sinan);
		turn180(sinan);
		sinan.Move (abs(x));}	
	
	if (y>=0)	//MOVEMENT IN Y-DIRECTION. If the input's difference between target is positive these lines will be realized
	{	turneast(sinan);
		turn270(sinan);
		sinan.Move(abs(y));}

	else  //MOVEMENT IN Y-DIRECTION. If the input's difference between target is negative these lines will be realized
	{	turneast(sinan);
		turn90right(sinan);
		sinan.Move(abs(y));}

	turneast(sinan); //after the final movement robot turns to east
}

int main ()
{
	int inputx, inputy ; //user will input a x and y value. They will be integers and defined here

	GetInput("Please enter an x value: ", inputx);	//I ask user to enter a x value
	if (terminate (inputx)) //if written value is lower than 0, program will terminate itself
  {

	GetInput("Please enter a y value: ", inputy);	//I ask user to enter a y value
	if(terminate(inputy))	//if written value is lower than 0, program will terminate itself
	{
		int distance1= abs(abs(inputx-8)+abs(inputy-6));			//absolute value of distance difference is calculated for each of targets.
		int distance2= abs(abs(inputx-2)+abs(inputy-3));			
		int distance3= abs(abs(inputx-4)+abs(inputy-10));

		Robot sinan (inputx, inputy);	//user decides on a x and y value and plugs an input, robot is created in that location
		sinan.SetColor(yellow);		

		if (isfirstsmallest(distance1, distance2, distance3)) //distance comparison is held by the bool function
			{
				yallah(8-inputx, 6-inputy,sinan);		//if the input is close to target 1, locomotion will be initialized
				sinan.SetColor(blue);					// when robot moves to its first target it changes its color as blue
				yallah(-4,4, sinan);					//then robot will move to its next targets as defined in the homework instructions
				yallah(-2,-7,sinan);
			}
	
			else if (isfirstsmallest(distance2, distance3, distance1))
				{
					yallah(2-inputx,3-inputy,sinan);	//if the input is close to target 2, locomotion will be initialized
					sinan.SetColor(blue);				// when robot moves to its first target it changes its color as blue. 
					yallah(2,7, sinan);					//then robot will move to its next targets as defined in the homework instructions
					yallah(4,-4,sinan);
				}

				else if (isfirstsmallest(distance3, distance2, distance1))
					{
						yallah(4-inputx,10-inputy,sinan);	//if the input is close to target 3, locomotion will be initialized
						sinan.SetColor(blue);				// when robot moves to its first target it changes its color as blue
						yallah(4,-4, sinan);				//then robot will move to its next targets as defined in the homework instructions
						yallah(-6,-3,sinan);
					}

	return 0;
	}
  }
}