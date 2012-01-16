// Filename:      DELTATASK.H
// Author:          	C. DAVYDUKE
// File Created:   03/11/22
// Last Modified: 03/11/22
// Description:     This file contains the class definitions for the consent multi-tasking base class.

#ifndef __DELTATASK_H__
#define __DELTATASK_H__

#include "task.h"

class DeltaTaskList : public TaskList
{
  public:
    void block( int msec );
    void decrement();  // dec top entries time
    bool zero();  // is top entry time == 0?
  private:
    virtual void insert( TaskList::Node * );
    int time;  // temporary
    void block();  // avoid offering original block()
};

#endif
