// Filename:		ISR.CPP
// Author:			C. DAVYDUKE
// File Created:	03/10/20
// Last Modified: 03/10/29
// Description:	This file contains the class methods for interrupt service routines and interrupt controllers.

#include "isr.h"

// Here are the methods for the interrupt service routine
//Isr::Isr( class Ictlr & ic, unsigned int i )
Isr::Isr( Ictlr & ic, unsigned int i )
:	ictlr( ic ),
	index( i )
{
	ictlr.attach( this );
}

Isr::~Isr()
{
	ictlr.detach( this );
}

void Isr::handler()	// default handler
{
}

// Here are the methods for the interrupt controllers
Ictlr::Ictlr( unsigned int len )
:	length( len ),
	isrTbl( new Isr * [length] )
{
	for( unsigned int i = 0; i < length; i++ )
		isrTbl[i] = 0;
}

Ictlr::~Ictlr()
{
	delete[] isrTbl;
}

void Ictlr::attach( Isr * isr )
{
	if( isr->index < length )
		isrTbl[isr->index] = isr;
}

void Ictlr::detach( Isr * isr )
{
	if( isr->index < length )
		isrTbl[isr->index] = 0;
}
