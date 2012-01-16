// Filename:		OUTPUTCOMPARE.H
// Author:			C. DAVYDUKE
// File Created:	03/10/21
// Last Modified: 03/10/29
// Description:	This file contains the class definitions for outputcompare.

#ifndef __OUTPUTCOMPARE_H__
#define __OUTPUTCOMPARE_H__

#include "chipio.h"

class OutputCompare	// Controls 1 oc channel of the 8
{
	private:
		volatile unsigned int & tcx;		// A reference to one of the TC0-TC7 compare registers
		unsigned mask;	// 1 << num ( chan number )
		unsigned level;	// Choose one of the 4 possible actions
		unsigned mode;	// on compare.

	public:
		OutputCompare( int num, bool enable = false )
		:	tcx( ( & tc0 )[num] ),
			mask( 1 << num ),
			level( ol << ( 2 * num ) ),
			mode( om << ( 2 * num ) )
			{
				tscr |= ( ten | tffca );	// Set up tcnt and interrupt ack system
				tcx = tcnt - 1;		// Set max time till next compare
				tios |= mask;		// Set channel to compare mode

				if( enable )
				{
					tflg1 |= mask;	// ack any previous int.
					tmsk1 |= mask;	// enable the interrupt.
				}
			}

		~OutputCompare()
		{
			// fill in later
		}

		operator unsigned int() const	// conversion operator
		{
			return tcx;
		}

		void at( unsigned time )
		{
			tcx = time;
		}

		void raiseAt( unsigned time )
		{
			tctl1 |= mode;
			tctl1 |= level;
			at( time );
		}

		void dropAt( unsigned time )
		{
			tctl1 |= mode;
			tctl1 &= ~level;
			at( time );
		}

		void oc7( int level )
		{
			if( level < 0 )
			{
				oc7m &= ~mask;
				oc7d &= ~mask;
			}

			else
			{
				if( level )
					oc7d |= mask;
				else
					oc7d &= ~mask;
				oc7m |= mask;
			}
		}
};

#endif
