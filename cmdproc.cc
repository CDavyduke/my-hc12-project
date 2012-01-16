// Filename:		CMDPROC.CC
// Author:			C. DAVYDUKE
// File Created:	03/10/19
// Last Modified: 03/10/22
// Description:	This file contains the class methods for the command base class and the command processor base class.

#include "ctype.h"
#include "string.h"
#include "iomanip.h"
#include "strstream.h"
#include "cmdproc.h"

Cmd::Cmd( const char * n )
:	name( n )
{
}

const char * Cmd::parse( istream &, ostream & )
{
	return 0;
}

bool Cmd::match( istream & is )
{
	char buf[20];
	return is >> setw( sizeof( buf ) ) >> buf
		&& strcmp( buf, name ) == 0;
}

CmdProc::CmdProc( streambuf * sb, const char * p )
:	sbuf( sb ),
	prompt( p )
{
}

void CmdProc::present( Cmd * menu[] )
{
	while( 1 )
	{
		istream is( sbuf );
		ostream os( sbuf );
		// show the prompt
		os << endl << prompt << flush;
		char buf[80];			// input buffer
		char * bp = buf;		// char * bp = &buf[0]
		char * ep = &buf[ sizeof( buf ) - 1 ];	// point to the end of the buffer
		int done = 0;

		while( !done )			// get a line from the user
		{
			int c = is.get();	// get one char from the istream, unformatted

			switch( c )
			{
				case '\r':
				case '\n':
					*bp = 0;		// terminate input buffer
					done = 1;	// exit while loop
					break;
				case 'H'-0x40:// backspace
					if( bp > buf )
					{
						os << "\b \b" << flush;	// Move cursor back once, enter space, move cursor back
						--bp;
					}
					break;
				default:
					if( isprint( c ) && bp < ep )
					{
						os.put( c );// echo char
						os.flush();
						*bp++ = c;// buffer char
					}
					break;
			}
			
		}

		if( buf[0] != 0 )	// avoid error on empty line
		{
			const char * error = "unknown command";
			for( Cmd ** cmd = &menu[0]; * cmd; ++cmd )	// iterate over menu
			{
				istrstream iss( buf );	// create an istream whose source is a char buff
				if( ( * cmd ) -> match( iss ) )
				{
					error = ( * cmd ) -> parse( iss, os );
					break;
				}
			}

			if( error )
				os << endl << "Error: " << error;
		}
	}
}
