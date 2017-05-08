#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the human version of the game

	AI machine;

	//at start, create all states using states files
	machine.readActions("actions.txt");

	string input;
	cout << "Welcome to the game of Hangman. Enter a 5-letter word and the AI will try to guess it with 10 strikes." << endl;
	cin >> input;

	while(input.size() != 5 || std::find_if(input.begin(), input.end(), non_alpha()) != input.end())
	{
		cout << "Please enter a 5 letter word." << endl;
		cin >> input; 
	}

	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	string currentboard = "_____";
	char letter;

	machine.printBoard(currentboard);

	while(ifWin(currentboard) == 0 && machine.ifLoss() == 0)
	{
		letter = machine.chooseActionHuman(currentboard);
		currentboard = machine.guess(letter,currentboard,input);
	}

	int winCheck = ifWin(currentboard);
	machine.printBoard(currentboard);

	if(winCheck == 1)
	{
		cout << "You Lost." << endl; 
		machine.learningFactorWin();
	}
	else
	{
		cout << "You Won." << endl;
		machine.learningFactorLoss();
	}

	machine.writeActions("actions.txt");
}