// Filename:	  MUTEX.CC
// Author:	  C. DAVYDUKE
// File Created:  03/12/17
// Last Modified: 03/12/20
// Description:	  This file contains the class methods for the mutex base class.

#include "mutex.h"
#include "interrupts.h"

Mutex::Mutex()
: holder( 0 )
{
}

void Mutex::acquire()
{
  Interrupts masked;  // lock
  while( holder )         // while !ready
    block();                // block & unlock, lock
  holder = getCurrent();  // use
}                             // unlock

void Mutex::release()
{
  Interrupts masked;  // lock
  holder = 0;             // make ready
  unblock();              // unblock
}                             // unlock
