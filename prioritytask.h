// Filename:        PRIORITYTASK.H
// Author:          C. DAVYDUKE
// File Created:    03/12/03
// Last Modified:   03/12/03
// Description:     This file contains the class definition for the piority 
//                  task list.

#ifndef __PRIORITYTASK_H__
#define __PRIORITYTASK_H__

#include "task.h"

class PriorityTaskList : public TaskList
{
  public:
    PriorityTaskList( Task * task = 0 )
    : TaskList( task )
    {
    }
    
  private:
    virtual void insert( TaskList::Node * );
};

#endif
