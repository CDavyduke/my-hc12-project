// Filename:		      TIMERTASK.CC
// Author:			       C. DAVYDUKE
// File Created:	   03/11/22
// Last Modified: 03/12/09
// Description:	   This file contains the class definitions for the consent multi-tasking base class.


#include "timertask.h"
#include "chipio.h"

TimerTask * TimerTask::theTimerTask;  // singleton

TimerTask::TimerTask( size_t stackSize, unsigned int priority, Ictlr & ictlr, int index, int r )
: Task( stackSize, priority ),
  Isr( ictlr, index ),
  rate( r )
{
  theTimerTask = this;
  ddrdlc |= ( 1 << 1 );
  portdlc &= ~( 1 << 1 ); // set bit 1 to zero to start.
}

TimerTask::~TimerTask()
{
  theTimerTask = 0;
}

void TimerTask::delay( int msec )
{
  if( theTimerTask )
    theTimerTask->deltaList.block( msec );
}

void TimerTask::main()
{
  while( 1 )
  {
    waitList.block();
    portdlc ^= ( 1 << 1 );  // toggle bit 1 each time task blocks.
    for( int i = 0; i < rate; i++ )
    {
      deltaList.decrement();
      while( deltaList.zero() )
        deltaList.unblock();
    }
  }
}

void TimerTask::handler()
{
  waitList.unblock();
}
