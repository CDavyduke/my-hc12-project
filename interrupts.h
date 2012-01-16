// Filename:		INTERRUPTS.H
// Author:			C. DAVYDUKE
// File Created:	03/10/20
// Last Modified: 03/10/29
// Description:	This file contains the class definition of interrupts and some low level code.

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

// This class definition allows us to use the properties of classes (e.g. constructors and
// destructors) to ensure that interrupts are always enabled and disabled, and one or
// the other is not forgotten.  Very HC12 specific.
class Interrupts
{
	public:
		Interrupts()
		{
			asm( "tfr ccr, b" );
			asm( "std %0" : : "m"(oldMask) : "d" );
			asm( "sei" );
		}
		~Interrupts()
		{
			asm( "ldd %0" : : "m"(oldMask) : "d" );
			asm( "tfr b, ccr" );
		}

	private:
		int oldMask;
};

#endif
