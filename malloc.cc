// Filename:		MALLOC.CC
// Author:			C. DAVYDUKE
// File Created:	03/10/08
// Last Modified:	03/10/17
// Description:	This file contains the code to allocate memory.

#include "malloc.h"
#include "stddef.h"

extern char heap_beg;
extern char heap_top;
 
static char * freePtr = &heap_beg;

// We allocate memory using a "one-way" allocator.
void * malloc( size_t size )
{
	void * callPtr = freePtr;

	if( ( freePtr += size ) < &heap_top )
		return callPtr;

	else
		return 0;
  
}

// Also in the spirit of a one way allocator, we do not
// have a way to de-allocate the memory.
void free( void * )
{
}
