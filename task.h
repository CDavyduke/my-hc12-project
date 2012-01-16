// Filename:      TASK.H
// Author:        C. DAVYDUKE
// File Created:  03/11/22
// Last Modified: 03/12/20
// Description:   This file contains the class definitions for the consent multi-tasking base class.

#ifndef __TASK_H__
#define __TASK_H__

#include "stddef.h"

class Task
{
  public:
    Task( size_t stackSize, unsigned int priority );
    virtual ~Task();
    static void yield();  // switch to next task
    bool lowerPriorityThan( const Task * task ) const
    {
      return priority > task->priority;
    }
  protected:
    void fork();  // begin task execution
    virtual void main();  // task code
  private:
    static Task * current; // the running task.
    static void start();
    static void dispatch( Task * );  // switch Tasks
    friend class TaskList;
  private:
    void * * stack;  // the task stack
    void * * sp;  // sp when not running
    unsigned int priority;
};

class TaskList  // SLL (singely linked list) of tasks
{
  public:
    TaskList( Task * initial = 0 );
    virtual ~TaskList();
    void block();  // block the caller on this list
    void unblock();  // unblock first Task from list
    Task * getCurrent();
  protected:
    struct Node  // a node on the list
    {
      Node( class Task * t )
      : next( 0 ),
        task( t )
      {
      }
      Node * next;  // next node on the list
      Task * task;
      int time; // for use on DeltaTaskList
    };
    Node * first;  // first node on the list
  private:
    virtual void insert( Node * );
    Node * remove();
};

#endif
