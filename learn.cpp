#include <iostream>
#include <fstream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the AI vs AI version of the game

	ifstream myfile;
	ofstream myfile2;

 	myfile.open ("states.csv");
 	myfile2.open ("potentialStates.txt");

 	string state;
 	int xs, os;
 	while ( getline ( myfile, state, ',') )
 	{
		xs = 0, os = 0;

 		for(int i = 0; i < 10; i++)
 		{
 			if(state[i] == 'X')
 				xs++;
 			if(state[i] == 'O')
 				os++;
 		}

 		if(xs == os || (xs == os + 1))
	 		myfile2 << state;
 	}

	myfile.close();
	myfile2.close();

}