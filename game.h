struct action
{
		float value;
		int location;
};

struct state
{
		string board;
		vector<action> actions;
};

class AI 
{
private:

public: //move to private and add getters/setters for final code
	char token;
	state currentState;
	//std::stack<state> stack;
	std::vector<state> states;

	AI(char value) {token = value;}
	action chooseActionHuman(string s);
	//action chooseActionLearn( int player, state s, player p);
	void learningFactor(int winner, int loser, state finalStateWinner, state finalStateLoser);
	void readActions(string readFile);
	void writeActions(string writeFile);
};

//implement hash table for "have I been to this state before" to optimize for bigger state spaces