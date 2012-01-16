// Filename:      LTC1404.CC
// Author:        C. DAVYDUKE
// File Created:  03/12/20
// Last Modified: 03/12/20
// Description:   This file contains the class methods for the Ltc1404 base class.

#include "ltc1404.h"
#include "timertask.h"
#include "chipio.h"

// Had to create this dumb stuff to satisfy compiler
void Ltc1404::main()
{
  while( 1 )
  {
    portdlc ^= ( 1 << 6 );
    int raw;
    raw = Ltc1404SpiUser( spi );
    // do something useful with raw
    TimerTask::delay( time );
    yield();
  }
}
