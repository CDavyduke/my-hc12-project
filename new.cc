// Filename:			NEW.CC
// Author:				C. DAVYDUKE
// File Created:		03/10/08
// Last Modified:		03/10/21
// Description:		This file contains the code so that we can use operator new.

#include "new.h"
#include "stddef.h"
#include "malloc.h"
#include "fatalheaperr.h"

void * operator new( size_t size )
{
	void * callPtr = malloc( size );

	if( !( callPtr ) )			// If the heap is exhausted, malloc
	{								// will return a null pointer.  If the heap
		EnterSafeMode();	// is exhausted, there is nothing meaningful
		SetErrorFlag();		// to do except restart.
		Restart();
	}

	return callPtr;				// If malloc worked, return the pointer.
}

void * operator new[]( size_t size )
{
	void * callPtr = malloc( size );

	if( !( callPtr ) )			// If the heap is exhausted, malloc
	{								// will return a null pointer.  If the heap
		EnterSafeMode();	// is exhausted, there is nothing meaningful
		SetErrorFlag();		// to do except restart.
		Restart();
	}

	return callPtr;				// If malloc worked, return the pointer.
}

void operator delete( void * callPtr )
{
	free( callPtr );
}

void operator delete[]( void * callPtr )
{
	free( callPtr );
}
