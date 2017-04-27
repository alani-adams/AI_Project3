#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;

#include "game.h"

string AI::chooseActionHuman(string s) 
{
	//choose randomly taking values in to consideration, 
	//favor exploitation (choosing higher values disproportionately).

	//check possible actions for that player
	float highestValue = -1000; //because values could be negative
	int bestLocation = 0;

	std::vector<state>::iterator it;
	std::vector<action>::iterator it2, save, check;
	for(it = states.begin(); it < states.end(); it++)
	{
		if(s == it->board)
		{	
			for(it2 = it->actions.begin(); it2 < it->actions.end(); it2++)
			{
				if(it2->value > highestValue)
				{
					highestValue = it2->value;
					bestLocation = it2->location;
					save = it2;
				}
			}
			stack.push(save);
			break;
		}
	}
	s[bestLocation] = token;
	return s;

}

//TODO: rewrite
// action AI::chooseActionLearn(string s) 
// {
// 	//choose randomly taking values in to consideration, 
// 	//favor exploration (choosing lower values disproportionately), 
// 	//choose highest value or random when equal
// 	//int randNum1 = rand() % 100;
// 	//add all the values together and multiply by 100. get rand() % that num and see which one it would fall into
// 	int valueSum=0;
// 	int valueProb[9];
// 	/*TODO: need to find corresponding state in vector before referencing actions vector of that state*/
// 	for(int i=0; i<p.actions.size(); i++)
// 	{
// 		valueSum += (p.actions[i].value * 100);
// 		valueProb[i] = valueSum;
// 	}
// 	int randNum = rand() % valueSum;

// 	if(0<randNum && randNum<valueProb[1])
// 	{
// 		a.value = p.actions[0].value;
// 		a.location = p.actions[0].location;
// 		return a;
// 	}

// 	for(int i=0; i<(p.actions.size()-1); i++)
// 	{
// 		for(int j=1; j<p.actions.size(); j++)
// 		{
// 			if(valueProb[i]<randNum && randNum<valueProb[j])
// 			{
// 				a.value = p.actions[j].value;
// 				a.location = p.actions[j].location;
// 				return a;
// 			}
// 		}
// 	}
// 	//add pointer to action to the stack of actions taken
// 	return a;
// }

void AI::learningFactorWin() //applies learning feature
{
	std::vector<action>::iterator move = stack.top(); //get top action to edit its value
	move->value = 1; //set last action to be value of 1 because it leads to an immediate win
	stack.pop(); //rm the last action from the stack

	float decay = 1;
	while(stack.size() != 0)
	{
		move = stack.top();
		move->value += (move->value * (0.1 * decay));
		decay *= 0.2;
		stack.pop();
	}
}

void AI::learningFactorLoss() //applies learning feature
{
	std::vector<action>::iterator move;

	float decay = 1;
	while(stack.size() != 0)
	{
		move = stack.top();
		move->value -= (move->value * (0.1 * decay));
		decay *= 0.2;
		stack.pop();
	}
}

int ifWin(string board)
{
	//continue == 0, winner player1 == 1, winner player2 == 2, draw == 3
	if((board[0] == board[1] && board[0] == board[2]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[1] && board[0] == board[2]) && (board[0] == 'O') )
		return 2;
	else if((board[3] == board[4] && board[3] == board[5]) && (board[3] == 'X') )
		return 1;
	else if((board[3] == board[4] && board[3] == board[5]) && (board[3] == 'O') )
		return 2;
	else if((board[6] == board[7] && board[6] == board[8]) && (board[6] == 'X') )
		return 1;
	else if((board[6] == board[7] && board[6] == board[8]) && (board[6] == 'O') )
		return 2;
	else if((board[0] == board[3] && board[0] == board[6]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[3] && board[0] == board[6]) && (board[0] == 'O') )
		return 2;
	else if((board[1] == board[4] && board[1] == board[7]) && (board[1] == 'X') )
		return 1;
	else if((board[1] == board[4] && board[1] == board[7]) && (board[1] == 'O') )
		return 2;
	else if((board[2] == board[5] && board[2] == board[8]) && (board[2] == 'X') )
		return 1;
	else if((board[2] == board[5] && board[2] == board[8]) && (board[2] == 'O') )
		return 2;
	else if((board[0] == board[4] && board[0] == board[8]) && (board[0] == 'X') )
		return 1;
	else if((board[0] == board[4] && board[0] == board[8]) && (board[0] == 'O') )
		return 2;
	else if((board[2] == board[4] && board[2] == board[6]) && (board[2] == 'X') )
		return 1;
	else if((board[2] == board[4] && board[2] == board[6]) && (board[2] == 'O') )
		return 2;

	bool draw = true;
	for(int i=0; i<9; i++)//checking if there are no moves left
	{
		if(board[i] == '_')
			draw = false;
	}
	if(draw)
		return 3;
	return 0;
}

void AI::writeActions(string writeFile) //send vector (either Xstates or Ostates) and corresponding actions output file
{
	ofstream actionsFile;
 	actionsFile.open (writeFile);

 	std::vector<state>::iterator it;
 	std::vector<action>::iterator it2;
 	for(it = states.begin(); it < states.end(); it++)
 	{	
 		actionsFile << it->board << endl;
 		for(it2 = it->actions.begin(); it2 < it->actions.end(); it2++)
	 	{
	 		actionsFile << it2->location << " " << it2->value << endl;
	 	}
 	}

	actionsFile.close();
}

void AI::readActions(string readFile) //send vector of states and corresponding action file to read from
{
	ifstream read;
 	read.open (readFile);

 	string item;

 	while ( getline ( read, item) )
 	{
 		if(item[0] == '_' || item[0] == 'X' || item[0] == 'O')
 		{
 			state myState;
 			myState.board = item;
 			states.push_back(myState);
 		}
 		else
 		{
 			//if action, create action and add to current state's vector of actions
 			action myaction;

 			//convert to int for location and float for value
 			myaction.location = item[0] - '0';
 			string value(item.begin()+2, item.end()); //rm location int and space from string when copying to value
 			const char* value2 = value.c_str();
 			myaction.value = strtof(value2, NULL);
 			states.back().actions.push_back(myaction);
 		}
 	}

	read.close();
}

void printBoard(string board)
{
	for(int i = 0; i < 10; i++)
	{
		if(i % 3 == 0)
		{
			cout << endl;
			if(i == 3 || i == 6)
			cout << "---|---|---" << endl;
		}
		else
			cout << '|';
		if(board[i] != '_')
			cout << " " << board[i] << " ";
		else
			cout << "   ";
	}
	cout << endl;
}

