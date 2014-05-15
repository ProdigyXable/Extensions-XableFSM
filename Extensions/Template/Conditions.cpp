
#include "Common.h"

// Immediate Condition
bool Extension::NewState()
{
	return true;
}

// Immediate Condition
bool Extension::AnyTransition()
{
	return true;
}

bool Extension::SpecificTransition_Key(float key)
{
	if(StateMachine[0]->last_state_key == key)
	{
		return true;
	}
	return false;
}

bool Extension::SpecificTransition_Name(TCHAR * name)
{
	if(StateMachine[0]->last_state_name == name)
	{
		return true;
	}

	return true;
}

bool Extension::OutputMessage()
{
	bool state_found = false;
	unsigned int index = 0;

	while(!state_found && index < StateMachine.size())
	{
		if(StateMachine[index]->current_state_key == StateMachine[index]->key)
		{
			return (StateMachine[index]->output_message != 0);
		}

		index++;
	}

	return true;
}

bool Extension::StateJustRemoved()
{
	return true;
}
bool Extension::LostState()
{
	return true;
}
bool Extension::TooFewStates()
{
	return true;
}
bool Extension::EmptySystem()
{
	return true;
}
bool Extension::BadSignal()
{
	return true;
}