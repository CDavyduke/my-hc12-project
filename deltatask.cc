// Filename:        DELTATASK.CC
// Author:           C. DAVYDUKE
// File Created:   03/11/22
// Last Modified: 03/12/03
// Description:     This file contains the class methods for the consent multi-tasking base class.

#include "deltatask.h"
#include "interrupts.h"
#include "task.h"

void DeltaTaskList::block( int msec )
{
  Interrupts masked;
  time = msec;  // save temporarily
  TaskList::block();
}

void DeltaTaskList::insert( TaskList::Node * node )
{
  Interrupts masked;
  
  if( node )
  {
    node->time = time;  // set delay time of node
    
    if( Node * tempNode = (this)->first )
    {
      int sumTimes = tempNode->time;
      
      while( tempNode->next )                 // Find the current sum total of the
      {                                                   // times of the currently existing tasks.
        tempNode = tempNode->next;
        sumTimes += tempNode->time;
      } 
        
      if( node->time >= sumTimes )  // We'll take care of the case where the new
      {                                           // node is added to the end of the list here.
        node->time -= sumTimes;
        tempNode->next = node;
        node->next = 0;
      }
      
      else
      {
        Node * prevNode = (this)->first;
        
        if( node->time < prevNode->time ) // This takes care of the case where
        {                                                 // the node is added to the beginning 
          prevNode->time -= node->time;   // of a pre-existing list.
          node->next = prevNode;
          (this)->first = node;
        }
        
        else      // This else statements takes care of the case where the
        {           // node is added somewhere in the middle of the list.
          Node * nextNode = 0;
          int prevSum = prevNode->time;
          int nextSum = 0;
          int bContinue = 1;
        
          while( prevNode->next && bContinue )
          {
            nextNode = prevNode->next;        
            nextSum = prevSum + nextNode->time;
          
            if( ( node->time >= prevSum ) && ( node->time <= nextSum ) )
            {
              node->time -= prevSum;
              nextNode->time -= node->time;
              node->next = nextNode;
              prevNode->next = node;
              bContinue = 0;
            }
        
            prevNode = nextNode;
            prevSum += prevNode->time;
          } // end of while( nextNode->next )
        } // end of else, covering all cases insertting a node into middle of the list.
      } // end of else, covering all cases where the new nodes time greater than first.
    } // end of if( Node * tempNode = (this)->first ), covering all cases where a first node
      // already exists on the list.
    else                          // This takes care of the case where the task to be added
    {                               // is the first one added to the list.
      (this)->first = node;
      node->next = 0;
    }
  } // end of if( node )
}

void DeltaTaskList::decrement()
{
  if( first )
    --first->time;
}

bool DeltaTaskList::zero()
{
  return first && first->time <= 0;
}
