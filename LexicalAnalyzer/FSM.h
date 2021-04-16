#pragma once

/*FSM class:
*	Keeps track of state machine
*
* Methods:
*	SetCurrentState: sets the current state of the machine
*	GetNextState: Gets the next state in the machine
* Constructor: Creates class and sets maximum states
*
* Private Variables:
*	currentState: track of the current state
*	state: track of which state it will be
*	maxStates: Max states the machine can have
*/
class FSM
{
protected:
	int currentState;
	int state;
	int maxState;

	void SetCurrentState(int newState)
	{
		state = newState;
	}

	int GetNextState()
	{
		currentState++;
		if (currentState > maxState) 
			currentState = 1;
		return currentState;
	}

public:
	FSM(int maxState)
	{
		this->maxState = maxState;
		this->currentState = 0;
		this->state = 0;
	}
};