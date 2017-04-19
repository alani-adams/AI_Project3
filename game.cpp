#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <stdlib.h> 
using namespace std;

#include "game.h"

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
			act.value = 0.5;//IDK WHAT THE VALUE IS!!!!!!!!! Do we need to look it up somehow?
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

void evaluate(string board) // finds the best action to take
{
	//checks for actions
	//selects best action

	int location=0;//chosen move/action //dependent on data
	if(turn == 1)
		s.board[location] = 'X';
	else
		s.board[location] = 'O';
	action a;
	a.value = 0.5;//NOT SURE, dependent on data
	a.location = location;
	s.actions.insert(a);

}

chooseAction() 
{
	//choose randomly taking values in to consideration, 
	//favor exploration (choosing lower values disproportionately), 
	//favor exploitation (choosing higher values disproportionately).


}

void learningFactor(int winner, int loser, state finalStateWinner, state finalStateLoser) //applies learning feature
{
	//apply 1 to last move
	finalStateWinner.actions[finalStateWinner.actions.size()].value = 1;
	float decay = 1;
	for(int i=1; i<finalStateWinner.actions.size(); i++)
	{
		finalStateWinner.actions[i].value += (finalStateWinner.actions[i].value * (0.1 * decay));
		decay *= 0.2;
	}

	decay = 1;
	for(int i=1; i<finalStateLoser.actions.size(); i++)
	{
		finalStateLoser.actions[i].value -= (finalStateLoser.actions[i].value * (0.1 * decay));
		decay *= 0.2;
	}
}

int ifWin(string board)
{
	//continue == 0, winner player1 == 1, winner player2 == 2, draw == 3
	if((board[0] == board[1] == board[2]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[1] == board[2]) && (board[0] == 'O') )
		return 2;
	else if((board[3] == board[4] == board[5]) && (board[3] == 'X') )
		return 1;
	else if((board[3] == board[4] == board[5]) && (board[3] == 'O') )
		return 2;
	else if((board[6] == board[7] == board[8]) && (board[6] == 'X') )
		return 1;
	else if((board[6] == board[7] == board[8]) && (board[6] == 'O') )
		return 2;
	else if((board[0] == board[3] == board[6]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[3] == board[6]) && (board[0] == 'O') )
		return 2;
	else if((board[1] == board[4] == board[7]) && (board[1] == 'X') )
		return 1;
	else if((board[1] == board[4] == board[7]) && (board[1] == 'O') )
		return 2;
	else if((board[2] == board[5] == board[8]) && (board[2] == 'X') )
		return 1;
	else if((board[2] == board[5] == board[8]) && (board[2] == 'O') )
		return 2;
	else if((board[0] == board[4] == board[8]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[4] == board[8]) && (board[0] == 'O') )
		return 2;
	else if((board[2] == board[4] == board[6]) && (board[2] == 'X') )
		return 1;
	else if((board[2] == board[4] == board[6]) && (board[2] == 'O') )
		return 2;

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

void writeActions(std::vector<state> states, string writeFile) //send vector (either Xstates or Ostates) and corresponding actions output file
{
	ofstream actions;
 	actionsFile.open (writeFile);

 	std::vector<state>::iterator it, it2;
 	for(it = states.begin(); it < states.end(); it++)
 	{	
 		actionsFile << it.board << endl;
 		for(it2 = it.actions.begin(); it2 < it.actions.end(); it2++)
	 	{
	 		actionsFile << it2.location << " " << it2.value << endl;
	 	}
 	}

	actionsFile.close();
}

void readActions(std::vector<state> states, string readFile) //send vector (either Xstates or Ostates) and corresponding action file to read from
{
	ifstream read;
 	read.open (readFile);

 	string item;
 	std::vector<state>::iterator current;
 	while ( getline ( read, item) )
 	{
 		if(item[0] == "_" || item[0] == "X" || item[0] == "O")
 		{
 			//if state, find state in vector and save as current
 			std::vector<state>::iterator it;
 			for(it = states.begin(); it < states.end(); it++)
 			{
 				if(item == it.board)
 				{
 					current = it;
 					break;
 				}
 			}
 		}
 		else
 		{
 			//if action, create action and add to current state's vector of actions
 			action myaction;

 			//convert to int for location and float for value
 			myaction.location = atoi(item[0]);
 			string value(item.begin()+2, item.end()); //rm location int and space from string when copying to value
 			myaction.value = strtof(value, NULL);

 			current.actions.push_back(myaction);
 		}
 	}

	read.close();
}
