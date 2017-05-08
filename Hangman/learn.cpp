#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
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
		letter = machine.chooseActionHuman(currentboard);
		currentboard = machine.guess(letter,currentboard,word);
		machine.printBoard(currentboard);
	}

	int winCheck = ifWin(currentboard);
	machine.printBoard(currentboard);

	if(winCheck == 1)
	{
		cout << "AI Won." << endl; 
		machine.learningFactorWin();
	}
	else
	{
		cout << "AI Lost." << endl;
		machine.learningFactorLoss();
	}

	machine.writeActions("actions.txt");
}