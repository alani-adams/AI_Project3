struct action
{
		float value;
		char letter;
};

struct state
{
		string board;
		vector<action> actions;
};

struct non_alpha {
    bool operator()(char c) {
        return !std::isalpha(c);
    }
};

class AI 
{
private:
	std::vector<char> strikes;
	std::stack<std::vector<action>::iterator> stack;
	std::vector<state> states;

public:
	char chooseActionHuman(string s);
	char chooseActionLearn(string s);
	void learningFactorWin();
	void learningFactorLoss();
	void readActions(string readFile);
	void writeActions(string writeFile);
	void printBoard(string board);
	void printStrikes();
	void addtoStrikes(char letter) {strikes.push_back(letter);}
	void createState(string s);
	int ifLoss();
	string guess(char letter, string board, string word);

};

string hangman[11] = {" ______\n |     |\n |\n |\n |\n |\n_|_", " ______\n |     |\n |     o\n |\n |\n |\n_|_ ", " ______\n |     |\n |     o\n |     |\n |     |\n |\n_|_", " ______\n |     |\n |     o\n |    /|\n |     |\n |\n_|_", " ______\n |     |\n |     o\n |   _/|\n |     |\n |\n_|_", " ______\n |     |\n |     o\n |   _/|\\\n |     |\n |\n_|_", " ______\n |     |\n |     o\n |   _/|\\_\n |     |\n |\n_|_", " ______\n |     |\n |     o\n |   _/|\\_\n |     |\n |    /\n_|_", " ______\n |     |\n |     o\n |   _/|\\_\n |     |\n |   _/\n_|_", " ______\n |     |\n |     o\n |   _/|\\_\n |     |\n |   _/ \\\n_|_", " ______\n |     |\n |     o\n |   _/|\\_\n |     |\n |   _/ \\_\n_|_"};

//go through all states we have and then if we don't already have the state, 
//we create it. when we create the state, we automatically generate all potential actions 
//and add them to the actions vector

//ran learning game > 102250 times