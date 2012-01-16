// Filename:		FATALHEAPERR.CC
// Author:			C. DAVYDUKE
// File Created:	03/10/21
// Last Modified:	03/10/21
// Description:	This file contains the code for handling a fatal heap error.

#include "fatalheaperr.h"
#include "restart.h"

// This would ordinarily contain some code to put the servo into a safe mode.
void EnterSafeMode( )	// Probably would do something like disable the
{									// laser in this case, turn off the TECs, etc.
}

// This would ordinarily contain some code to create an error flag of some sort.
void SetErrorFlag( )	// Could be visual, could be some data stored into the
{								// eeprom or flash, could be audible.
}
