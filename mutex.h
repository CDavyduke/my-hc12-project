// Filename:	     	MUTEX.H
// Author:		      	C. DAVYDUKE
// File Created:  	03/12/17
// Last Modified: 03/12/17
// Description:	  This file contains the class definition for the mutex base class.

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "task.h"

class Mutex : public TaskList
{
  public:
    Mutex();
    void acquire();  // wait operation
    void release();  // signal operation
  private:
    const Task * holder;  // the Task being pointed to cannot be changed 
};                                 //  by the holder.

#endif
