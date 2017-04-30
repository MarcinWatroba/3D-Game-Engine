#pragma once

#include "Engine/FSM/FSM_State.h"
#include <vector>

template <typename T>
class FSM
{
private:
	const std::vector<FSM_State<T>*>* states;
	unsigned int current;
	unsigned int previous;
	//get pointer to current state
	FSM_State<T>* CurrentState();
	//return index of state by given ID
	unsigned int FindState(unsigned int stateID);
	//change state
	void ChangeStates(unsigned int index);
protected:
	T data;
	void Run();
public:
	T* AccessData();
	//create a FSM with a given set of states and the ID of the starting state
	FSM(const std::vector<FSM_State<T>*>* stateList, unsigned int startStateID);
};




template <typename T>
FSM<T>::FSM(const std::vector<FSM_State<T>*>* stateList, unsigned int startStateID) :
	states(stateList)
{
	current = FindState(startStateID);
	previous = current;
}

template <typename T>
FSM_State<T>* FSM<T>::CurrentState()
{
	return (*states)[current];
}

template <typename T>
unsigned int FSM<T>::FindState(unsigned int stateID)
{
	//iterate over states to find the state with the given ID
	for (size_t i = 0; i < states->size(); i++)
	{
		if ((*states)[i]->StateID() == stateID)
		{
			return i;
		}
	}
	//state was not found
	throw std::invalid_argument("given state ID not found in state list");
}

template <typename T>
void FSM<T>::ChangeStates(unsigned int index)
{
	//finish current state
	CurrentState()->Finish();
	//set previous state to the current state
	previous = current;
	//set current state to the new state
	current = index;
}

template <typename T>
T* FSM<T>::AccessData()
{
	return &data;
}

template <typename T>
void FSM<T>::Run()
{
	fsm::FSM_Command result = CurrentState()->Run(AccessData());

	switch (result)
	{
	case fsm::Continue:
		//do nothing
		break;

	case fsm::Finish:
		//end current state and return to previous state
		ChangeStates(previous);
		break;

	case fsm::Switch:
		//end current state and switch to new state
		ChangeStates(FindState(CurrentState()->NextDesiredStateID()));
		break;
	}
}