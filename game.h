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

public:
	state currentState;
	std::stack<state> stack;
	std::vector<state> states;

}

class Human 
{
private:

public:
	
}



//implement hash table for "have I been to this state before" to optimize for bigger state spaces