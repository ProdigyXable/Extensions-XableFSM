
#include "Common.h"

int Extension::States::state_count = 0;
TCHAR * Extension::States::current_state_name = (TCHAR *)"";
float Extension::States::current_state_key = 0;
TCHAR *	Extension::States::last_state_name = (TCHAR *)"";
float Extension::States::last_state_key = 0;

void Extension::AddState(TCHAR * name, float key, int active_output, float output_integer, TCHAR * output_message)
{
	 StateMachine.push_back(new Extension::States(name, key, active_output, output_integer, output_message));
	 Runtime.GenerateEvent(StateAdded);
}

void Extension::RemoveState_Name(TCHAR * name)
{
	bool state_removed = false;

	if(StateMachine.size() > 0)
	{
		for(unsigned int index = 0; index < StateMachine.size(); index++)
		{
			if( (_tcscmp(StateMachine[index]->name, name) == 0) && state_removed == false)
			{
				// Precaution against memory leaks
				delete StateMachine[index];
				StateMachine[index] = NULL;

				StateMachine.erase(StateMachine.begin() + index);
				state_removed = true;
				Runtime.GenerateEvent(StateRemoved);
			}
		}

		Runtime.GenerateEvent(StateNotFound);
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
	}
}

void Extension::RemoveState_Key(float key)
{
	bool state_removed = false;

	if(StateMachine.size() > 0)
	{
		for(unsigned int index = 0; index < StateMachine.size(); index++)
		{
			if(StateMachine[index]->key == key && state_removed == false)
			{
				// Precaution against memory leaks
				delete StateMachine[index];
				StateMachine[index] = NULL;

				StateMachine.erase(StateMachine.begin() + index);
				state_removed = true;
				Runtime.GenerateEvent(StateRemoved);
			}
		}	

		Runtime.GenerateEvent(StateNotFound);
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
	}
}

void Extension::TransitionState_Key(float key)
{
	if(StateMachine.size() > 0)
	{
		for(unsigned int index = 0; index < StateMachine.size(); index++)
		{
			if(StateMachine[index]->key == key)
			{
				StateMachine[index]->current_state_key = key;
				StateMachine[index]->current_state_name = StateMachine[index]->name;

				return;
			}
		}
	
		Runtime.GenerateEvent(StateNotFound);
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
	}
}

void Extension::TransitionState_Name(TCHAR * name)
{
	if(StateMachine.size() > 0)
	{
		for(unsigned int index = 0; index < StateMachine.size(); index++)
		{
			if(_tcscmp(StateMachine[index]->name, name) == 0)
			{
				StateMachine[index]->current_state_key = StateMachine[index]->key;
				StateMachine[index]->current_state_name = name;

				return;
			}
		}

 		Runtime.GenerateEvent(StateNotFound);
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
	}
}

void Extension::ChangeOutput_Key(float key, int active_output, float output_integer, TCHAR * output_message)
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(StateMachine[index]->key == key)
		{
			StateMachine[index]->active_output = active_output;
			StateMachine[index]->output_integer = output_integer;
			StateMachine[index]->output_message = output_message;
		}
	}

	Runtime.GenerateEvent(StateNotFound);

	return;
}

void Extension::ChangeOutput_Name(TCHAR * name, int active_output, float output_integer, TCHAR * output_message)
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(_tcscmp(StateMachine[index]->name,name) == 0)
		{
			StateMachine[index]->active_output = active_output;
			StateMachine[index]->output_integer = output_integer;
			StateMachine[index]->output_message = output_message;
		}
	}

	Runtime.GenerateEvent(StateNotFound);

	return;
}