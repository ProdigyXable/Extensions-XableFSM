#pragma once

// #define TGFEXT       // TGF2, MMF2, MMF2 Dev
   #define MMFEXT       // MMF2, MMF2 Dev
// #define PROEXT       // MMF2 Dev only

#include    "Edif.h"
#include	"Resource.h"

#define StateMachine Extension::State_System

// -- Custom Shortcuts -- 
#define StateAdded 0
#define StateRemoved 5
#define NullSize 8
#define StateNotFound 6
#define SignalOff 9

// edPtr : Used at edittime and saved in the MFA/CCN/EXE files

struct EDITDATA
{
	// Header - required
	extHeader		eHeader;

	// Object's data
//	short			swidth;
//	short			sheight;

};

#include "Extension.h"
