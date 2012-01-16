// Filename:		    HC12TIMERTASK.CC
// Author:			     C. DAVYDUKE
// File Created:  	03/11/22
// Last Modified: 03/12/09
// Description:	  This file contains the class definitions for the consent multi-tasking base class.

#include "hc12timertask.h"
#include "hc12ictlr.h"
#include "chipio.h"

HC12TimerTask::HC12TimerTask( size_t stackSize, unsigned int priority, Ictlr & ictlr )
: TimerTask( stackSize, priority, ictlr, HC12Ictlr::isRti, 1 << (rtres - 1 ) )
{
  rtictl = rti + rtres;
  fork();
  ddrdlc |= 1;  // set bit 0 up as an output
  portdlc &= ~1;  // set bit 0 to zero to start.
}

HC12TimerTask::~HC12TimerTask()
{
  rtictl = ~rti & 0xff;
}

void HC12TimerTask::handler()
{
  rtiflg = rti;
  portdlc ^= 1; // toggle bit 0 each time handler is run.
  TimerTask::handler();
}
