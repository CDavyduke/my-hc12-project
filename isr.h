// Filename:		ISR.H
// Author:			C. DAVYDUKE
// File Created:	03/10/20
// Last Modified: 03/10/29
// Description:	This file contains the class definitions for interrupt service routines and interrupt controllers.

#ifndef __INTCTLR_H__
#define __INTCTLR_H__

class Isr
{
	protected:
//		Isr( class Ictlr &, unsigned int index );
		Isr( class Ictlr &, unsigned int index );	// forward reference to Ictlr
		virtual ~Isr();

	private:
		virtual void handler();	// the actual interrupt service routine.
//		class Ictlr & ictlr;
		Ictlr & ictlr;
		unsigned int index;

		friend class Ictlr;	// Ictlr has access to private (& protected) members.
};

class Ictlr
{
	public:
		Ictlr( unsigned int len );	// len is max Isr's
		virtual ~Ictlr();
		void attach( Isr * isr );		// attach and detach an isr to the controller.
		void detach( Isr * isr );

	protected:
		void runHandler( unsigned int index )
		{
			if( isrTbl[index] )		// If an Isr is in table, run its handler
				isrTbl[index] -> handler();
		}

	private:
		unsigned int length;
		Isr * * isrTbl;
};

#endif
