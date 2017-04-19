#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
using namespace std;

#include "learning.h"

int ifWin(string board)
{
	//continue == 0, winner player1 == 1, winner player2 == 2, draw == 3
	if((board[0] == board[1] == board[2]) && (board[0] == 'X') )
		return learningFactor(1,2);
	else if((board[0] == board[1] == board[2]) && (board[0] == 'O') )
		return learningFactor(2,1);
	else if((board[3] == board[4] == board[5]) && (board[3] == 'X') )
		return learningFactor(1,2);
	else if((board[3] == board[4] == board[5]) && (board[3] == 'O') )
		return learningFactor(2,1);
	else if((board[6] == board[7] == board[8]) && (board[6] == 'X') )
		return learningFactor(1,2);
	else if((board[6] == board[7] == board[8]) && (board[6] == 'O') )
		return learningFactor(2,1);
	else if((board[0] == board[3] == board[6]) && (board[0] == 'X') )
		return learningFactor(1,2);
	else if((board[0] == board[3] == board[6]) && (board[0] == 'O') )
		return learningFactor(2,1);
	else if((board[1] == board[4] == board[7]) && (board[1] == 'X') )
		return learningFactor(1,2);
	else if((board[1] == board[4] == board[7]) && (board[1] == 'O') )
		return learningFactor(2,1);
	else if((board[2] == board[5] == board[8]) && (board[2] == 'X') )
		return learningFactor(1,2);
	else if((board[2] == board[5] == board[8]) && (board[2] == 'O') )
		return learningFactor(2,1);
	else if((board[0] == board[4] == board[8]) && (board[0] == 'X') )
		return learningFactor(1,2);
	else if((board[0] == board[4] == board[8]) && (board[0] == 'O') )
		return learningFactor(2,1);
	else if((board[2] == board[4] == board[6]) && (board[2] == 'X') )
		return learningFactor(1,2);
	else if((board[2] == board[4] == board[6]) && (board[2] == 'O') )
		return learningFactor(2,1);

	bool draw = true;
	for(int i=0; i<9; i++)//checking if there are no moves left
	{
		if(board[i] == '_')
			draw == false;
	}
	if(draw)
		return 3;
	return 0;
}

state possibleStates( state s, string board, int player )
{
	int count=0;
	for(int i=0; i<9; i++)//count how many open spots
	{
		if(board[i] == '_')
			count++;
	}


	for(int j=0; j<9; j++)
	{
		string temp = board;
		
		if(board[j] == '_')
		{
			action act;
			act.location = j;
			act.value = 0.5;//IDK WHAT THE VALUE IS!!!!!!!!!!!!!!
			if(player == 1)
			{
				temp[j] = 'X';

			}
			else
			{
				temp[j] = 'O';

			}
			s.possibleActions.insert(act);
		}
	}
}

newState()
{

}

evaluate()
{

}

chooseState()
{

}

int learningFactor(int winner, int loser)
{
	//apply 1 to last move



	return winner;
}


