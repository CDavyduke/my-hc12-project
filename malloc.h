// Filename:		MALLOC.H
// Author:		C. DAVYDUKE
// File Created:	03/10/08
// Last Modified:	03/10/12
// Description:		This file contains the header information, declarations,
//			etc, needed for malloc.cc

#include "stddef.h"
#ifndef __MALLOC_H__
#define __MALLOC_H__
void * malloc( size_t size);
void free( void * );
#endif
