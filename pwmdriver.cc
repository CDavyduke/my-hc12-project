// Filename:       PWMDRIVER.CC
// Author:         C. DAVYDUKE
// File Created:   03/10/21
// Last Modified:  03/11/29
// Description:	This file contains the class methods for PWM driver.

#include "pwm.h"
#include "interrupts.h"
#include "hc12ictlr.h"

PwmDriver::PwmDriver( Ictlr & ic, unsigned per )
: Isr( ic, HC12Ictlr::isTc3 ),
  first( 0 ),
  period( per ),
  phase( 0 ),
  ocTick( 3, true ),
  ocOff( 7 )
{
  ocTick.at( tcnt + period / 2 );
}

void PwmDriver::handler( )  // ints globally masked by HC12, automatically
{
  ocTick.at( ocTick + period / 2 );  // set time of next event to time of this event + period / 2
  phase = ( phase + 1 ) & 1;

  if( phase == 0 )
    ocOff.at( ocTick + period / 2 );  // set up Oc7 to generate falling edge on Pwm

  for( PwmChannel * chan = first; chan;
    chan = chan -> handler( phase, ocOff ) );

}

PwmChannel * PwmDriver::attach( PwmChannel * chan )
{
  Interrupts masked;
  PwmChannel * list = first;
  first = chan;
  return list;
}
