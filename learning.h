struct action
{
		float value;
		int location;
		//string board;
};

struct state
{
		string board;
		vector<action> actions;
};