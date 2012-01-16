// Filename:		NEW.H
// Author:		C. DAVYDUKE
// File Created:	03/10/08
// Last Modified:	03/10/12
// Description:		This file contains the header information (function
//			prototypes, declarations, ect) for new.cc

#include "stddef.h"

#ifndef __NEW_H__
#define __NEW_H__
void * operator new( size_t size );
void * operator new[]( size_t size );
void operator delete( void * );
void operator delete[]( void * );
#endif
