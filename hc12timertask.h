// Filename:	     	HC12TIMERTASK.H
// Author:			       C. DAVYDUKE
// File Created:  	03/11/22
// Last Modified: 03/12/09
// Description:	  This file contains the class definitions for the consent multi-tasking base class.

#ifndef __HC12TIMERTASK_H__
#define __HC12TIMERTASK_H__

#include "timertask.h"
#include "chipio.h"

class HC12TimerTask : public TimerTask
{
  public:
    HC12TimerTask( size_t stackSize, unsigned int priority, Ictlr & ictlr );
    virtual ~HC12TimerTask();
  private:
    virtual void handler();
    const int rtres = rtr1;  // rate, real-time resolution, rtr1 from chipio
};

#endif
