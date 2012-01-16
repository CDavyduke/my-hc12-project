// Filename:		RESTART.CC
// Author:			C. DAVYDUKE
// File Created:	03/10/21
// Last Modified:	03/10/21
// Description:	This file contains the code for for restarting.

#include "restart.h"

// Maybe it makes sense to have the restart command in one separate
// file, maybe it does not.  I'm not sure yet, but there may be other
// reasons or files that need to call Restart.
void Restart( void )
{
	asm( "jmp _start" );
}
