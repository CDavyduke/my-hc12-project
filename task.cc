// Filename:	  TASK.CC
// Author:	  C. DAVYDUKE
// File Created:  03/11/22
// Last Modified: 03/12/20
// Description:	  This file contains the class methods for the consent multi-tasking base class.

#include "task.h"
#include "prioritytask.h"
#include "interrupts.h"
#include "priorities.h"

// static variables
Task initialTask( 0, priInitTask );  // the initial task
Task * Task::current = & initialTask;

// task switching
register void * * hwsp asm( "s" ); // GCC magic

// forces variable hwsp into register "s", stack pointer
void Task::dispatch( Task * task )
{
  current->sp = hwsp;  // save reg s in current->sp
  current = task;  // choose new current task
  hwsp = current->sp;  // loag reg s from current->sp
}

// task list creation
TaskList::TaskList( Task * task )
: first( task ? new Node( task ) : 0 )
{
}

TaskList::~TaskList()
{
}

// ready list -- list of all tasks in "ready" state
PriorityTaskList _readyList( & initialTask );
TaskList & readyList( _readyList );

// low-level list manipulation
void TaskList::insert( Node * node )  // insert at tail of list
{                                                    // -- implies a search for the end
  if( node )
  {
    Node * tempNode;

    if( !(this)->first )
      (this)->first = node;

    else
    {
      for( tempNode = (this)->first; tempNode->next; tempNode = tempNode->next );

      tempNode->next = node;
    }

    node->next = 0;
  }
}

TaskList::Node * TaskList::remove()  // remove Node from head of list
{
  // lab exercise
  Node * tempNode = (this)->first;
  (this)->first = tempNode->next;
  tempNode->next = 0;
  return tempNode;
}

// task state changes
void TaskList::block()
{
  Interrupts masked;
  insert( readyList.remove() );  // remove head task from readyList (running task) inser on this list
  Task::dispatch( readyList.first->task ); // switch to new first task on ready list
}

void TaskList::unblock()
{
  Interrupts masked;
  readyList.insert( remove() );  // remove first task from this list, insert into readyList
  Task::dispatch( readyList.first->task ); // switch to new first task on ready list
}

Task * TaskList::getCurrent()
{
  Interrupts masked;
  return readyList.first->task;
}

void Task::yield()  // give up CPU to another task by moving self to end of readyList
{
  readyList.block();
}

// creating & starting tasks
void Task::main()  // do nothing and return immediately
{
}

void Task::start()
{
  asm( "cli" );
  current->main();  // run the task code
  TaskList temp;  // avoid returning from start()
  temp.block();  // consumes no further CPU cycles
}  // never reached

Task::Task( size_t stackSize, unsigned int p )
: stack( new ( void * )[ stackSize / sizeof( void * ) ] ),
  sp( & stack[ stackSize / sizeof( void * ) ] ),
  priority( p )
{
  if( stackSize ) // if ! initialTask
  {
    *--sp = 0; // terminate return chain
    *--sp = 0; // terminate frame chain
    *--sp = &start; // push address of Task::start()
  }
}

Task::~Task()
{
  delete stack;
}

void Task::fork()  // called by most-derived ctor
{
  TaskList temp( this );
  temp.unblock();
}
