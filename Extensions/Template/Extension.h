
class Extension
{
public:

    LPRDATA rdPtr;
    LPRH    rhPtr;

    Edif::Runtime Runtime;

    static const int MinimumBuild = 251;
    static const int Version = 1;

    static const int OEFLAGS = 0;
    static const int OEPREFS = 0;
    
    static const int WindowProcPriority = 100;

    Extension(LPRDATA rdPtr, LPEDATA edPtr, fpcob cobPtr);
    ~Extension();

	class States
	{
		public:
			TCHAR *	name;
			float	key;
		
			int		active_output;
			float	output_integer;
			TCHAR *	output_message;

			static int		state_count;
			static TCHAR *	current_state_name;
			static float	current_state_key;

			static float	last_state_key;
			static TCHAR *	last_state_name;

			States(TCHAR * name, float key, int active_output, float output_integer, TCHAR * output_message)
			{
				// IDs
				this->name = name;
				this->key = key;

				// Possible Output Parameters
				this->active_output = active_output;
				this->output_integer = output_integer;
				this->output_message = output_message;

				this->state_count++;

				// Sets first state as the default state
				if(this->state_count == 1)
				{
					Extension::States::current_state_name = this->name;
					Extension::States::current_state_key = this->key;
					Extension::States::last_state_key = -1;
					Extension::States::last_state_name = (TCHAR *)"NULL";
				}		
			}

			States()
			{
			
			}

			~States()
			{
				this->state_count--;
			
				if((this->key == this->current_state_key))
				{
					// NULL:ASD stands for "NULL: Active State Deleted"
					Extension::States::current_state_name = (TCHAR *)"NULL: ASD";
					Extension::States::current_state_key = -1;
				}
			}
	};

	 vector<States *> State_System;


    /*  Add any data you want to store in your extension to this class
        (eg. what you'd normally store in rdPtr)

        Unlike rdPtr, you can store real C++ objects with constructors
        and destructors, without having to call them manually or store
        a pointer.
    */

    /*  Add your actions, conditions and expressions as real class member
        functions here. The arguments (and return type for expressions) must
        match EXACTLY what you defined in the JSON.

        Remember to link the actions, conditions and expressions to their
        numeric IDs in the class constructor (Extension.cpp)
    */

    ///Actions
	
	void AddState(TCHAR * name, float key, int active_output, float output_integer, TCHAR * output_message);
	void RemoveState_Name(TCHAR * name);
	void RemoveState_Key(float key);

	
	void ChangeOutput_Key(float key, int active_output, float output_integer, TCHAR * output_message);
	void ChangeOutput_Name(TCHAR * name, int active_output, float output_integer, TCHAR * output_message);
	void TransitionState_Key(float key);
	void TransitionState_Name(TCHAR * name);
	

    /// Conditions

	bool NewState();
	bool AnyTransition();
	bool SpecificTransition_Key(float key);
	bool SpecificTransition_Name(TCHAR * name);
	bool OutputMessage();

	bool StateJustRemoved();
	bool LostState();
	bool TooFewStates();
	bool EmptySystem();
	bool BadSignal();
	

    // Expressions
	
	int StateCount();
	TCHAR * NameFromKey(float key);
	float KeyFromName(TCHAR * name);

	float CurrentStateKey();
	TCHAR * CurrentStateName();
	
	float  CurrentOutput_Key();
	TCHAR * CurrentOutput_Name();

    /* These are called if there's no function linked to an ID */

    void Action(int ID, LPRDATA rdPtr, long param1, long param2);
    long Condition(int ID, LPRDATA rdPtr, long param1, long param2);
    long Expression(int ID, LPRDATA rdPtr, long param);

    /*  These replace the functions like HandleRunObject that used to be
        implemented in Runtime.cpp. They work exactly the same, but they're
        inside the extension class.
    */

    short Handle();
    short Display();

    short Pause();
    short Continue();

    bool Save(HANDLE File);
    bool Load(HANDLE File);

};