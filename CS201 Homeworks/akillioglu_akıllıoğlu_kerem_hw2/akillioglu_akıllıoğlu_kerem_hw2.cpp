//	Kerem AKILLIOGLU 24179
#include <iostream> /* Selected and used libraries are written*/
#include <string>

using namespace std;



bool doesithave(string ingredient)
	/*Question is aked to a user whether given ingredient is wanted or not. The string parameter will named as “foam” or “water” in the following.
	When answered as “yes”, this function returns true. When answered as “no”, this function returns false. */
{
	string answer;
	cout<< "Does it have "<< ingredient <<"? "<<endl;
	cin >> answer;

	if (answer == "yes"){
		return true;
	}

	else if (answer =="no")
	{return false;}
}

bool askquestion(string n1, string n2)
	/*Asked to the user whether the given ingredients are in the equal amounts or not. 
	The string parameters will be ingredients such as “milk” or “foam”. */
{
	string response;
	cout <<"Do "<<n1<<" and "<<n2<<" are in equal amounts?"<< endl;
	cin >> response;
	if (response == "yes")	// When answered as “yes”, this function returns true
	{return true;}
	else if (response == "no")
	{return false;} //When answered as “no”, this function returns false.
}

void displayanswer(string name, string coffeetype)	//Username is received, resulting coffee gathered as a parameter, and a message displayed.
{
	cout <<"Your order is ready "<<name<<"! What you want is "<<coffeetype<<". Enjoy!"<< endl;
}

void programfunction(string person)
	/* 
	This function receives username as parameter, and it will call bool functions when needed.
	Asks the questions based on the flow chart*/

{
	cout<<"Dear "<<person<<", would you kindly answer our questions, so we can determine the coffee you want."<< endl; 

	if (doesithave("espresso"))
	{
		if (doesithave("milk"))	
		{
			if (doesithave("hot chocolate"))
			{displayanswer(person, "a mocha");}

			else
			{
				if	(doesithave("foam")){
					if (askquestion("foam","milk")){
						displayanswer(person,"a cappucino");
					}

					else
					{
						displayanswer(person, "a latte");
					}
					;}

				else
				{displayanswer(person,"a cafe au lait");}

				;}

			;}


		else
		{
			if (doesithave("water"))
			{displayanswer(person,"an americano");}
			else 
			{displayanswer(person,"an espresso");}
			;}
		;}

	else
	{(displayanswer(person,"a filtered coffee"));}

}

int main() /*This is the main function. */
{
	string firstname;
	cout<< "Welcome to Pequod's Coffee! Can you tell me your name?"<<endl; //user's name is asked
	cin>> firstname;//user's name is received

	programfunction(firstname);//calls the function to ask questions and determine the coffe type user have chosen
	cout<<endl;

	cout<< "Welcome to Pequod's Coffee! Can you tell me your name?"<<endl; // the same operations will be done for the second time
	cin>> firstname;

	programfunction(firstname);

	cin.get(); //prevented the program to close right after it ran
	cin.ignore();
	return 0; //the end 
}