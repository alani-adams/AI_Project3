#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	srand(time(NULL));
	//this is the computer run version of the game (random pick word to play with)
	AI machine;

	//at start, create all states using states files
	machine.readActions("actions.txt");

	//choose random word
	string word = chooseWord("5letters.txt");
	cout << "The word is " << word << endl;
	
	string currentboard = "_____";
	char letter;

	machine.printBoard(currentboard);

	while(ifWin(currentboard) == 0 && machine.ifLoss() == 0)
	{
		letter = machine.chooseActionLearn(currentboard);
		currentboard = machine.guess(letter,currentboard,word);
	}

	int winCheck = ifWin(currentboard);

	if(winCheck == 1)
	{
		cout << "AI Won." << endl; 
		machine.learningFactorWin();
	}
	else
	{
		machine.printBoard(currentboard);
		cout << "AI Lost." << endl;
		machine.learningFactorLoss();
	}

	machine.writeActions("actions.txt");
}