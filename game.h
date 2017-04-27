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
	char token;
	std::stack<std::vector<action>::iterator> stack;
	std::vector<state> states;

public:
	AI(char value) {token = value;}
	string chooseActionHuman(string s);
	//action chooseActionLearn( int player, state s, player p);
	void learningFactorWin();
	void learningFactorLoss();
	void readActions(string readFile);
	void writeActions(string writeFile);
};

//implement hash table for "have I been to this state before" to optimize for bigger state spaces