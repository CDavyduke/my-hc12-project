// Filename:		CMDPROC.H
// Author:			C. DAVYDUKE
// File Created:	03/10/19
// Last Modified: 03/10/22
// Description:	This file contains the class definitions for the command base class and the command processor base class.

#include "iostream.h"

#ifndef __CMDPROC_H__
#define __CMDPROC_H__

class Cmd
{
	public:
		Cmd( const char * name );
		bool match( istream & );		// Attempt to match the user's command with our name.
		virtual const char * parse( istream &, ostream & );	// Attempt to parse commands and args (if any).

	private:
		const char * name;
};

class CmdProc
{
	public:
		CmdProc( streambuf * sbuf, const char * prompt );

	protected:
		void present( Cmd * menu[] );		// present the menu

	private:
		streambuf * sbuf;
		const char * prompt;
};

#endif
