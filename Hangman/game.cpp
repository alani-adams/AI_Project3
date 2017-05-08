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
#include <cctype>
using namespace std;

#include "game.h"

string AI::guess(char letter, string board, string word)
{
	bool found = false;
	std::vector<char>::iterator it;
	for(int i = 0; i < 5; i++)
	{
		if(word[i] == letter)
		{
			found = true;
			board[i] = letter;
		}
	}

	if(!found)
	{
		strikes.push_back(letter);
		printBoard(board);
	}
	else
	{
		cout << "\nBoard: " << board << endl;
		cout << letter << " was found!" << endl;
	}

	return board;
}

void AI::createState(string s)
{
	state myState;
	myState.board = s;
	states.push_back(myState);

 	for(char letter = 'a'; letter <= 'z'; letter++)
 	{
 		if( s.find(letter) != std::string::npos )
    		continue;
		else 
		{
			action myaction;
			myaction.letter = letter;
			myaction.value = 0.5;
			states.back().actions.push_back(myaction);				
		}
 	}
}

char AI::chooseActionHuman(string s)
{
	float highestValue = -1000;
	char bestLetter = 'a';
	bool found = false;

	std::vector<state>::iterator it;
	std::vector<action>::iterator it2, save;
	for(it = states.begin(); it < states.end(); it++)
	{
		if(s == it->board)
		{	
			for(it2 = it->actions.begin(); it2 < it->actions.end(); it2++)
			{
				if(it2->value > highestValue && !(std::find(strikes.begin(), strikes.end(), it2->letter) != strikes.end()) )
				{
					highestValue = it2->value;
					bestLetter = it2->letter;
					save = it2;
					found = true;
				}
			}
			stack.push(save);
			break;
		}
	}

	if(!found) //haven't visited this state and must create new state and actions
	{
		createState(s);	
		for(it2 = states.back().actions.begin(); it2 < states.back().actions.end(); it2++)
		{
			if(it2->value > highestValue && !(std::find(strikes.begin(), strikes.end(), it2->letter) != strikes.end()) )
			{
				highestValue = it2->value;
				bestLetter = it2->letter;
				save = it2;
			}
		}
		stack.push(save);
	}

	return bestLetter;

}

char AI::chooseActionLearn(string s) 
{
	int valueSum=0, h = 0;
	int valueProb[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<state>::iterator it;
	std::vector<action>::iterator it2, save;
	bool found = false, set = false;
	char bestLetter = 'a';

	for(it = states.begin(); it < states.end(); it++)
	{
		if(it->board == s)
		{
			found = true;

			for(it2 = it->actions.begin(); it2 < it->actions.end(); it2++)
			{
				if(!(std::find(strikes.begin(), strikes.end(), it2->letter) != strikes.end()) )
				{
					if(!set)
					{
						save = it->actions.begin();
						set = true;
					}

					valueSum += (it2->value * 100);
					h = it2->letter - 97;
					valueProb[h] = valueSum;
				}
			}
			break;
		}
	}

	if(!found) //haven't visited this state and must create new state and actions
	{
		createState(s);	
		for(it2 = states.back().actions.begin(); it2 < states.back().actions.end(); it2++)
		{
			if(!(std::find(strikes.begin(), strikes.end(), it2->letter) != strikes.end()) )
			{
				valueSum += (it2->value * 100);
				h = it2->letter - 97;
				valueProb[h] = valueSum;
			}
		}
		save = states.back().actions.begin();
	}

	int randNum = rand() % valueSum;

	if(randNum<valueProb[0] && !(std::find(strikes.begin(), strikes.end(), save->letter) != strikes.end()))
	{
		bestLetter = save->letter;
		stack.push(save);
		return bestLetter;
	}

	for(int i=0; i<26; i++)
	{
		for(int j=1; j<26; j++)
		{
			save++;

			if(valueProb[j] == 0)
				j++;

			if(valueProb[i]<=randNum && randNum<valueProb[j] && isalpha(save->letter) && !(std::find(strikes.begin(), strikes.end(), save->letter) != strikes.end()))
			{
				bestLetter = save->letter;
				stack.push(save);
				return bestLetter;
			}
		}
	}
	return bestLetter;
}

void AI::learningFactorWin() //applies learning feature
{
	std::vector<action>::iterator move = stack.top(); //get top action to edit its value
	move->value = 1; //set last action to be value of 1 because it leads to an immediate win
	stack.pop(); //rm the last action from the stack

	float decay = 1;
	while(stack.size() != 0)
	{
		move = stack.top();
		if(!(std::find(strikes.begin(), strikes.end(), move->letter) != strikes.end()))
		{
			move->value += (move->value * (0.1 * decay));
			if(move->value > 1)
			move->value = 1;
		}
		else
		{
			move->value -= (move->value * (0.1 * decay));
			if(move->value < 0)
			move->value = 0;
		}
		decay *= 0.01;
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
		if(!(std::find(strikes.begin(), strikes.end(), move->letter) != strikes.end()))
		{
			move->value += (move->value * (0.1 * decay));
			if(move->value > 1)
			move->value = 1;
		}
		else
		{
			move->value -= (move->value * (0.1 * decay));
			if(move->value < 0)
			move->value = 0;
		}
		decay *= 0.01;
		stack.pop();
	}
}

int ifWin(string board)
{
	bool win = true;
	for(int i=0; i<5; i++)//checking if there are no moves left
	{
		if(board[i] == '_')
			win = false;
	}
	if(win)
		return 1;
	return 0;
}

int AI::ifLoss()
{
	bool loss = true;
	if(strikes.size() != 10)
		loss = false;
	if(loss)
		return 1;
	return 0;
}

void AI::writeActions(string writeFile)
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
	 		actionsFile << it2->letter << " " << it2->value << endl;
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
 		if(item[1] != ' ') //if the second char is not a space, it must be a state rather than an action
 		{
 			state myState;
 			myState.board = item;
 			states.push_back(myState);
 		}
 		else
 		{
 			//if action, create action and add to current state's vector of actions
 			action myaction;

 			//convert to float for value
 			myaction.letter = item[0];
 			string value(item.begin()+2, item.end()); //rm letter char and space from string when copying to value
 			const char* value2 = value.c_str();
 			myaction.value = strtof(value2, NULL);
 			states.back().actions.push_back(myaction);
 		}
 	}

	read.close();
}

string chooseWord(string readFile)
{
	ifstream read;
 	read.open (readFile);

 	string item;
 	std::vector<string> words;

 	while ( getline ( read, item) )
 		words.push_back(item);

	read.close();

	int randWord = rand() % words.size();
	return words[randWord];
}

void AI::printBoard(string board)
{
	cout << "\nBoard: " << board << endl;
	printStrikes();

}

void AI::printStrikes()
{
	cout << "Strikes: " << strikes.size() << "/10, ";

	std::vector<char>::iterator it;
	int count = 0;
	if(strikes.size() != 0)
	{
		for(it = strikes.begin(); it < strikes.end(); it++)
	 	{	
	 		cout << *it << " ";
	 		count++;
	 	}
 		
	}
	else
	{
		cout << "none"; 
	}
		
	cout << endl;
 	cout << hangman[count] << endl;
}
