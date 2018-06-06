#include "qlearningShooting.h"
#include <random>
#include <iostream>
#include <iomanip>
namespace KStudio
{

	qlearningShooting::qlearningShooting()
	{

	}

	void qlearningShooting::train(int state)
	{
		initialize();

		//Perform learning trials starting at all initial states.
		for (int j = 0; j < (iterations); j++)
		{
			for (int i = 0; i < (no_of_initial_States); i++)
			{
				episode(state);
			} // i
		} // j

		  //Print out Q matrix.
		for (int i = 0; i < (qSize); i++)
		{
			for (int j = 0; j < (qSize); j++)
			{
				cout << setw(Goal_state) << Q[i][j];
				if (j < qSize) {
					cout << ",";
				}
			} // j
			cout << "\n";
		} // i
		cout << "\n";
	}

	void qlearningShooting::test(int state)
	{
		int newState;
		//Perform tests, starting at all initial states.
		for (int i = 0; i < iterations; i++) {
			currentState = state;
			current_state = currentState;
			newState = 0;

			do {
				newState = maximum(currentState, true);
				cout << currentState << ", ";
				currentState = newState;
				actions.push_back(currentState);
			} while (currentState < Goal_state);
			next_state = actions[0];
			cout << "3: Goal State reached" << endl;
			//cout << "ACTIONS TEST0:  " << actions[i] << "\n";
		} // i
	}

	void qlearningShooting::episode(int state)
	{
		currentState = state;

		//Travel from state to state until goal state is reached.
		do {
			chooseAnAction();
		} while (currentState == Goal_state);

		//When currentState = 5, run through the set once more to
		//for convergence.
		for (int i = 0; i < qSize; i++) {
			chooseAnAction();
		} // i
	}

	void qlearningShooting::chooseAnAction()
	{
		int possibleAction;

		//Randomly choose a possible action connected to the current state.
		possibleAction = getRandomAction(qSize, 0);

		if (R[currentState][possibleAction] >= 0) {
			Q[currentState][possibleAction] = reward(possibleAction);
			currentState = possibleAction;
		}
	}

	int qlearningShooting::getRandomAction(int upperBound, int lowerBound)
	{
		int action = 0;
		bool choiceIsValid = false;
		int range = (upperBound - lowerBound) + 1;

		//Randomly choose a possible action connected to the current state.
		while (!choiceIsValid)
		{
			//Get a random value between 0 and 6.
			action = lowerBound + rand() / (RAND_MAX / range);
			if (R[currentState][action] > -1)
			{
				choiceIsValid = true;
			}
		}
		return action;
	}

	void qlearningShooting::initialize()
	{
		srand(static_cast<unsigned>(time(0)));

		for (int i = 0; i < (qSize); i++) {
			for (int j = 0; j < (qSize); j++) {
				Q[i][j] = 0;
			} // j
		} // i
	}

	int qlearningShooting::maximum(int state, bool returnIndexOnly)
	{
		// if returnIndexOnly = true, a Q matrix index is returned.
		// if returnIndexOnly = false, a Q matrix element is returned.

		int winner;
		bool foundNewWinner;
		bool done = false;

		winner = 0;

		while (!done)
		{
			foundNewWinner = false;
			for (int i = 0; i < qSize; i++)
			{
				if (i != winner) {             // Avoid self-comparison.
					if (Q[state][i] > Q[state][winner])
					{
						winner = i;
						foundNewWinner = true;
					}
				}
			}

			if (foundNewWinner == false)
			{
				done = true;
			}
		}

		if (returnIndexOnly == true)
		{
			return winner;
		}
		return Q[state][winner];
	}

	int qlearningShooting::reward(int action)
	{
		return static_cast<int>(R[currentState][action] + (gamma * maximum(action, false)));
	}

}
