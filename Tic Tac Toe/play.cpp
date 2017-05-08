#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the human version of the game

	AI machine('X');

	//at start, create all states for Xs using states files
	machine.readActions("Xactions.txt");

	cout << "Welcome to the game of Tic Tac Toe. AI will go first and be X's, you will be O's." << endl;

	string currentboard = "_________";
	int turn = 1;
	int num;
	while(ifWin(currentboard) == 0)
	{
		if(turn == 1)
		{
			currentboard = machine.chooseActionHuman(currentboard);
			turn=2;
		}	
		else
		{
			printBoard(currentboard);
			cout << "Make your move. Enter 0-9 to place your piece in the corresponding spot." << endl;

			while(true)
			{
				cin >> num;
				if(currentboard[num] != '_')
				{
					cout << "Please pick an empty space.";
					continue;
				}
				else 
					break;
			}
			
			currentboard[num] = 'O';
			turn=1;
		}
	}

	int winCheck = ifWin(currentboard);
	printBoard(currentboard);

	if(winCheck == 1)
	{
		cout << "You Lost." << endl; 
		machine.learningFactorWin();
	}
	else if(winCheck == 2)
	{
		cout << "You Won." << endl;
		machine.learningFactorLoss();
	}
	else
	{
		cout << "You Tied." << endl;
	}
	machine.writeActions("Xactions.txt");
}