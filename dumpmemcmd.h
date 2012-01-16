// Filename:		DUMPMEMCMD.H
// Author:			C. DAVYDUKE
// File Created:	03/10/19
// Last Modified: 03/10/22
// Description:	This file contains the class definitions for the dump memory command.

#ifndef __DUMPMEMCMD_H__
#define __DUMPMEMCMD_H__
#include "cmdproc.h"
#include "stddef.h"

class DumpMemCmd : public Cmd
{
	public:
		DumpMemCmd( const char * name )
		:	Cmd( name )
		{
		}

		virtual const char * parse( istream & is, ostream & os )
		{
			size_t beg, end, i;
			
			if( !( is >> hex >> beg ) )		// get start address in hex
				return "need start";
			if( !( is >> hex >> end ) )		// get optional end address in hex
				end = beg + 0x40;			// default dump 4 lines

			os << endl << flush;

			for( i = beg; i <= end; i++ )
				os << int(*(reinterpret_cast<char*>(i))) << " " << flush;

			return 0;
		}
};

#endif

