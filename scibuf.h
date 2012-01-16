// Filename:		SCIBUF.H
// Author:			C. DAVYDUKE
// File Created:	03/10/16
// Last Modified: 03/10/16
// Description:		This file contains the class definition for the SCI (serial communications interface) buffer.

#include "stddef.h"
#include "chipio.h"
#include "iostream.h"

#ifndef __SCIBUF_H__
#define __SCIBUF_H__

class SciBuf : public streambuf
{
	public:
		SciBuf( volatile sciport& sci, size_t rxLen, size_t txLen );						// transmitter buffer length
		~SciBuf();

	protected:		// accessible to this class and derived members only.
		virtual int underflow();				// refill rx buff, retn 1st new char.
		virtual int overflow( int );			// empty tx buf & handle 1 more char.
		virtual int sync();					// empty tx buf.
	
	private:
		int poll();								// Check for rx char.
		char recv();							// Get rx char from port.
		void send( char );					// Send char to port.
		volatile sciport& sci;
		char * rxBuf;							// Start of rxBuf
		char * rxEnd;							// 1 past end of rxBuf
		char * txBuf;							// Start of txBuf
		char * txEnd;							// 1 past end of txBuf
};

#endif
