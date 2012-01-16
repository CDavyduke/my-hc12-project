// Filename:      TESTTASK.H
// Author:        C. DAVYDUKE
// File Created:  03/11/28
// Last Modified: 03/12/17
// Description:	This file contains the class definitions for the testtask class.

#ifndef __TESTTASK_H__
#define __TESTTASK_H__

#include "stddef.h"
#include "task.h"
#include "chipio.h"
#include "timertask.h"
#include "interrupts.h"

class TestTask : public Task
{
  public:
    TestTask( size_t ss, unsigned int p, unsigned int b, unsigned int c, int t )
    : Task( ss, p ),
      bitmask( b ),
      count( c ),
      time( t )
    {
      ddrdlc |= bitmask;
      portdlc &= ~bitmask;
      fork();
    }
    
  protected:
    virtual void main()
    {
      while( 1 )
      {
        TimerTask::delay( time );
	
	if( 1 )
	{
          Interrupts masked;  
	  portdlc &= ~bitmask;
	}
        
        for( unsigned int i = 0; i < count; i++ )
	{
	  Interrupts masked;
          portdlc ^= bitmask;
	}
          
        yield();
      }
    }
    
  private:
    unsigned int bitmask;
    unsigned int count;
    int time;
};

#endif
