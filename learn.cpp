#include <iostream>
#include "game.cpp"
using namespace std;

int main()
{
	//this is the AI vs AI version of the game

	//at start, create all states for Xs and Os using states files

	state currentState.board = "_________";
	int turn = 1;
	while(ifWin(currentBoard) == 0)
	{
		evaluateLearn(currentState, turn);

		if(turn == 1)
			turn=2;
		else
			turn=1;
	}

	if(ifWin(board, s) == 1)
		learningFactor(1,2,player1State, player2State);
	else if(ifWin(board, s) == 2)
		learningFactor(2,1,player2State,player1State);
	//draw
}