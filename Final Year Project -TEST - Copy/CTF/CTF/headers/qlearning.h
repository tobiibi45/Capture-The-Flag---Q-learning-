#pragma once
#include <ctime>
#include <vector>


using namespace std;
namespace KStudio
{

	class qlearning
	{
	public:

		qlearning();
		~qlearning(void) = default;

		////////////////////////////////////////// Q - LEARNING  /////////////////////////////////
		const static int qSize = 5; // q Table Size for Both row and Column is 4
		const double gamma = 0.8;
		const static int iterations = 5;
		const static int Goal_state = 3;
		const static int no_of_initial_States = 1;
		const int initialState = 0;
		int current_state = 0;
		int next_state = 0;
		int third_state = 0;

		std::vector<int> actions;

		//For Training/////////////////
		int R[qSize][qSize] = {
			{ -1,   1,  -1,  -1,  -1 },    //0 starting pos
			{ -1,  -1,   0,   0, 100 },    //1 red flag
			{ -1,   0,  -1,	  0,   0 },    //2 player
			{ -1,   0,   0,  -1,   0 },    //3 blue flag
			{ -1,   0,   0,   0,   0 } };  //3 blue base (enemy base)

		int Q[qSize][qSize];
		int currentState;

		void train(int state);
		void test(int state);
		void episode(int state);
		void chooseAnAction();
		int getRandomAction(int upperBound, int lowerBound);
		void initialize();
		int maximum(int state, bool returnIndexOnly);
		int reward(int action);
	};
}