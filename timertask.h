// Filename:		    TIMERTASK.H
// Author:			     C. DAVYDUKE
// File Created:  	03/11/22
// Last Modified: 03/12/09
// Description:	  This file contains the class definitions for the consent multi-tasking base class.

#ifndef __TIMERTASK_H__
#define __TIMERTASK_H__

#include "task.h"
#include "isr.h"
#include "stddef.h"
#include "deltatask.h"

class TimerTask : public Task, public Isr
{
  public:
    static void delay( int msec );
  protected:
    TimerTask( size_t stackSize, unsigned int priority, Ictlr & ictlr, int index, int rate );
    virtual ~TimerTask();
    virtual void handler();  // handler for Isr
  private:
    virtual void main();
    DeltaTaskList deltaList;  // where clients unit
    TaskList waitList;  // timer task waits here
    int rate;
    static TimerTask * theTimerTask;
};

#endif
