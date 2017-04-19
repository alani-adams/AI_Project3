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

std::vector<state> Xstates, Ostates;