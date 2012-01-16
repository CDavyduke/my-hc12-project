// Filename:		SCIBUF.H
// Author:			C. DAVYDUKE
// File Created:	03/10/16
// Last Modified: 03/11/29
// Description:	This file contains the class methods for the SCI (serial communications interface) buffer.

#include "scibuf.h"
#include "stddef.h"
#include "chipio.h"
#include "iostream.h"
#include "task.h"

SciBuf::SciBuf(	volatile sciport& s,	size_t rxLen, size_t txLen )
:
	sci(s),
	rxBuf( new char[rxLen] ),
	rxEnd( rxBuf + rxLen ),
	txBuf( new char[txLen] ),
	txEnd( txBuf + txLen )
{
	setg( rxBuf, rxEnd, rxEnd );		// force immediate underflow.
	setp( txBuf, txEnd );					// set pbase = pptr, and set epptr to empty put buffer.
	sci.sccr2 |= ( sci.re | sci.te );		// Enable rx's and tx's.
}

SciBuf::~SciBuf()
{
	sci.sccr2 &= ~( sci.re | sci.te );	// Disable rx's and tx's.
	delete( txBuf );
	delete( rxBuf );
}

int SciBuf::underflow()
{
	char * p = rxBuf;
    
	do
	{
		*p++ = recv();						// wait indefinitely, then get char, put where p
	}												// points, inc p.
	while( p < rxEnd && poll() );
    
	setg( rxBuf, rxBuf, p );
    
	return rxBuf[0] & 0xff;
}

int SciBuf::overflow( int c )
{
	sync();
    
	return sputc( c );						// put one char in buff at pptr, advance pptr
}

int SciBuf::sync()
{
	for( char * p = txBuf; p < pptr(); ++p )
		send( * p );							// Wait if necessary, send char

	setp( txBuf, txEnd );
    
	return 0;
}

int SciBuf::poll()								// retns true if rx char is immediately avail
{
	return sci.scsr1 & sci.rdrf;
}

char SciBuf::recv()
{
	while( !poll() )								// Note: Now yields while polling I/O.
		Task::yield();
	return sci.scdrl;
}

void SciBuf::send( char c )
{
	while( !( sci.scsr1 & sci.tdre ) )
		Task::yield();      // Note: Now yields while polling I/O.
	sci.scdrl = c;
}
