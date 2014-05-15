
#include "Common.h"



int Extension::StateCount()
{
	return StateMachine.size();
}

TCHAR * Extension::NameFromKey(float key)
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(StateMachine[index]->key == key)
		{
			return Runtime.CopyString(StateMachine[index]->name);
		}
	}
	return (TCHAR *)"NULL";
}

float Extension::KeyFromName(TCHAR * name)
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(_tcscmp(StateMachine[index]->name,name) == 0)
		{
			return StateMachine[index]->key;
		}
	}
	return -1;
}

float Extension::CurrentStateKey()
{
	if(Extension::StateCount())
	{
		return Extension::States::current_state_key;
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
		return -1;
	}
}

TCHAR * Extension::CurrentStateName()
{
	if(Extension::StateCount())
	{
		return Runtime.CopyString(Extension::States::current_state_name);
	}

	else
	{
		Runtime.GenerateEvent(NullSize);
		return (TCHAR *)"NULL";


	}
}

float Extension::CurrentOutput_Key()
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(StateMachine[index]->key == StateMachine[index]->current_state_key && StateMachine[index]->active_output != 0)
		{
			return StateMachine[index]->output_integer;
		}
		else if(StateMachine[index]->key == StateMachine[index]->current_state_key && StateMachine[index]->active_output == 0)
		{
			Runtime.GenerateEvent(SignalOff);
			return -2;
		}
	}

		Runtime.GenerateEvent(StateNotFound);

		return -1;
}

TCHAR * Extension::CurrentOutput_Name()
{
	for(unsigned int index = 0; index < StateMachine.size(); index++)
	{
		if(_tcscmp(StateMachine[index]->name,StateMachine[index]->current_state_name) == 0 && StateMachine[index]->active_output != 0)
		{
			return Runtime.CopyString(StateMachine[index]->output_message);
		}

		else if((_tcscmp(StateMachine[index]->name,StateMachine[index]->current_state_name) == 0 && StateMachine[index]->active_output == 0))
		{
			Runtime.GenerateEvent(SignalOff);
			return Runtime.CopyString((TCHAR *)"No Output Signal");
		}
	}
	
	Runtime.GenerateEvent(StateNotFound);

	// NULL: SNF means "NULL: State Not Found"
	return Runtime.CopyString((TCHAR *)"NULL: SNF");
}