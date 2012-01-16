// Filename:        PRIORITYTASK.CC
// Author:          C. DAVYDUKE
// File Created:    03/12/03
// Last Modified:   03/12/15
// Description:     This file contains the class methods for the piority 
//                  task list.

#include "prioritytask.h"
#include "task.h"
#include "interrupts.h"

void PriorityTaskList::insert( TaskList::Node * node )
{
  //excercise for the student
  Interrupts masked;
  
  if( node )
  {
    Task * nodeTask = node->task;
    
    if( first )
    {
      Node * tempNode = 0;
      Task * tempTask = 0;

      // Find last node (lowest priority)
      for( tempNode=first; tempNode->next; tempNode=tempNode->next );
      
      tempTask = tempNode->task;
      
      // Insert node at end of list if it is of the lowest priority
      if( nodeTask->lowerPriorityThan( tempTask ) )
      {
        tempNode->next = node;
        node->next = 0;
      }
      
      // Insert node somewhere in a pre-existing list
      else
      {
        Node * nextNode = first;
        Task * nextTask = nextNode->task;
        
        // Insert node at the head of the list if it is of the highest priority
        if( !nodeTask->lowerPriorityThan( nextTask ) )
        {
          node->next = nextNode;
          first = node;
        }

        // Insert node in the middle of the list in order of priority        
        else
        {
          Node * prevNode = 0;
          int bContinue = 1;
        
          while( nextNode->next && bContinue )
          {
            prevNode = nextNode;
            nextNode = nextNode->next;
            nextTask = nextNode->task;
          
            // If node's priority is between prev node and next node, we have found insert location
            if( !nodeTask->lowerPriorityThan( nextTask ) )
            {
              node->next = nextNode;
              prevNode->next = node;
              bContinue = 0;
            }
//            prevNode = nextNode;        
          } // end while
        } // end else (insert in the middle of a list in order of priority)
      } // end else (insert in a pre-existing list somewhere)
    } // end if( first )

    // If the list is empty (i.e. there is no first node), this node becomes the first node
    else
    {
      first = node;
      node->next = 0;
    }
  } // end if( node )
}
