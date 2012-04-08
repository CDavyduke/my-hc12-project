// Filename:        MAIN.CC
// Author:            C. DAVYDUKE
// File Created:    03/09/11
// Last Modified:  03/12/20
// Description:     This file contains the function main().

#include "new.h"
#include "scibuf.h"
#include "appcmdproc.h"
#include "hc12ictlr.h"
#include "pwm.h"
#include "testtask.h"
#include "stddef.h"
#include "hc12timertask.h"
#include "priorities.h"
#include "ltc1404.h"
#include "hc12spi.h"

// Needed to create bit masks for the test tasks.
const unsigned int bitmask2 = ( 1 << 2 );
const unsigned int bitmask4 = ( 1 << 4 );
const unsigned int bitmask5 = ( 1 << 5 );

const size_t stackSize = 512;

const int AdcTime = 100;  // in ms

int main( )
{  
  SciBuf * sciBuf = new SciBuf( sci0, 80, 16 );
  HC12Ictlr hc12Ictlr;
  PwmDriver pwmDriver( hc12Ictlr, 4000 );
  PwmChannel pwmChannel0( pwmDriver, 0 );
  PwmChannel pwmChannel1( pwmDriver, 1 );
  HC12TimerTask hc12TimerTask( stackSize, priHC12TmrTask, hc12Ictlr );
  HC12Spi hc12Spi( spi0 );
  Ltc1404 ltc1404( stackSize, priLTC1404Task, hc12Spi, AdcTime );
	
  ostream os( sciBuf );
  istream is( sciBuf );

  // Display introductory welcome message.
  os << "Hello, world!" << endl;

  TestTask * tt2 = 0;
  TestTask * tt4 = 0;
  TestTask * tt5 = 0;

  // Just some simple little tasks for toggling bits.
  tt2 = new TestTask( stackSize, priTestTask1, bitmask2, 5, 2 );
  tt4 = new TestTask( stackSize, priTestTask2, bitmask4, 1, 4 );
  tt5 = new TestTask( stackSize, priTestTask3, bitmask5, 250, 1000 );
  
  // Must create appCmdProc task last, otherwise above tasks never run.
  AppCmdProc appCmdProc( sciBuf, stackSize, priAppCmdProcTask,
    pwmChannel0, pwmChannel1 );
 
  // Code should never reach here, but just in case, clean up the heap.
  delete tt2;
  delete tt4;
  delete tt5;
    
  while( 1 )
    Task::yield();
  
  return 0;
}
