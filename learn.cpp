#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the AI vs AI version of the game

	//at start, create all states for Xs and Os using states files

	AI machine1('X');
	AI machine2('O');

	//at start, create all states for Xs using states files
	machine1.readActions("Xactions.txt");
	machine2.readActions("Oactions.txt");

	string currentboard = "_________";
	int turn = 1;
	while(ifWin(currentboard) == 0)
	{
		if(turn == 1)
		{
			printBoard(currentboard);
			currentboard = machine1.chooseActionHuman(currentboard);
			turn=2;
		}	
		else
		{
			printBoard(currentboard);
			currentboard = machine2.chooseActionHuman(currentboard);
			turn=1;
		}
	}

	int winCheck = ifWin(currentboard);
	printBoard(currentboard);

	if(winCheck == 1)
	{
		cout << "AI 1 was the winner.";
		learningFactor(1,2,player1State, player2State);
	}
	else if(winCheck == 2)
	{
		cout << "AI 2 was the winner.";
		learningFactor(2,1,player2State,player1State);
	}
	else
		cout << "AI 3 was the winner.";
	// there's a draw, for now we are not applying learningFactor in this case
}