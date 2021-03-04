#pragma once

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