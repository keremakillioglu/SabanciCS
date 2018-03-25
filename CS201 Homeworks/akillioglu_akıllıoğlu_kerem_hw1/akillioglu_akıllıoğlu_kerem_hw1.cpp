/* Kerem AKILLIOÐLU, 24179, HW1 */

#include <iostream>

using namespace std;

int main ()

{
	double  picprice, cakeprice, sculpprice, moneyforanimals, salerevenue  ; 
	int		soldpic, soldcake, soldsculp ;  

	/*
	picprice refers to unit price of pictures which is an input
	cakeprice refers to unit price of cakes which is an input
	sculpprice refers to unit price of sculptures which is an input
	soldpic refers to number of sold pictures which is an input
	soldcake refers to number of sold handmade cakes which is an input
	soldsculp refers to number of sold sculptures which is an input
	*/
	
	/*
	moneyforanimals refers to amount of money donated for animals which is an output.
	salerevenue refers to amount of money which is gathered at the end of the sale and is  an output. 
	 */

	cout << " Please enter the unit price of pictures: " ; 
	cin >> picprice;
	//unit price of painted pictures is asked from the user, user will enter an input and the user's input is defined as picprice

	cout << " Please enter the unit price of cakes: " ;
	cin >> cakeprice;
	//unit price of handmade cakes is asked from the user and the user's input is defined as cakeprice

	cout << " Please enter the unit price of sculptures: " ;
	cin >> sculpprice;
	//unit price of handmade sculptures is asked from the user and the user's input is defined as sculpprice

	cout << " Please enter the total number of pictures sold: " ;
	cin >> soldpic ;
	//number of sold pictures is asked from the user and the user's input is defined as soldpic

	cout << " Please enter the total number of cakes sold: " ;
	cin >> soldcake;
	//number of sold cakes is asked from the user and the user's input is defined as soldcake
	
	cout << " Please enter the total number of sculptures sold: " ;
	cin >> soldsculp ;
	//number of sold handmade sculptures is asked from the user and the user's input is defined as soldsculp

	salerevenue = (picprice * soldpic) + (cakeprice * soldcake) + (sculpprice * soldsculp) ;
	// this equation gives the value of the total revenue
	moneyforanimals = (salerevenue * 0.85) ;
	// this equation gives the amount which is donated for the animal shelters

	cout << " Total money gained: " << salerevenue<< endl;
	// total revenue of the sale is shown to the user

	cout << " Amount of money donated to the shelter: "  << moneyforanimals << endl;
	// donated money for animals is shown to the user

	cin.get();
	cin.ignore ();
	// cin.get() and cin.ignore() commands are written for preventing the program to close itself after it runs
	return 0 ;

}