#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the AI vs AI version of the game

	//at start, create all states for Xs and Os using states files

	string currentboard = "_________";
	int turn = 1;
	while(ifWin(currentBoard) == 0)
	{
		evaluateLearn(currentState, turn);

		if(turn == 1)
			turn=2;
		else
			turn=1;
	}

	winCheck = ifWin(board);
	if(winCheck == 1)
		learningFactor(1,2,player1State, player2State);
	else if(winCheck == 2)
		learningFactor(2,1,player2State,player1State);
	// there's a draw, for now we are not applying learningFactor in this case
}