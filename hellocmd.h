// Filename:		HELLOCMD.H
// Author:			C. DAVYDUKE
// File Created:	03/10/19
// Last Modified: 03/10/22
// Description:	This file contains the class definitions for the hello command.

#ifndef __HELLOCMD_H__
#define __HELLOCMD_H__
#include "cmdproc.h"

class HelloCmd : public Cmd
{
	public:
		HelloCmd( const char * name )
		:	Cmd( name )
		{
		}
		virtual const char * parse( istream &, ostream & os )
		{
			os << endl << "Hello, world!";
			return 0;
		}
};

#endif
