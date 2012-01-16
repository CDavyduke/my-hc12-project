// $Id: pwmchannel.cc,v 1.1 2003/11/13 04:26:24 cdavyduk Exp $

// pwmchannel.cc			   Copyright (C) 2003, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	PWM Channel
//
//---------------------------------------------------------------------------

#include "interrupts.h"
#include "chipio.h"
#include "hc12ictlr.h"
#include "pwm.h"


// The LMD18200 data sheet says that we must enforce a minimum delay between
// transitions on the PWM, DIR, and BRAKE lines

static const int transDelay = 8;	// minimum transition delay, tcnt's


//---------------------------------------------------------------------------
//
//	Pwm Channel Class
//

PwmChannel::PwmChannel(PwmDriver& dr, int num)
: next(0),
  driver(dr),
  dutyCycle(0),
  newOnTime(0),
  onTime(0),
  ocDir(num * 4),
  ocPwm(num * 4 + 1),
  ocBrk(num * 4 + 2)
{
  Interrupts masked;

  // set up oc7 action for PWM output

  ocPwm.oc7(0);

  // attach to channel list

  next = driver.attach(this);
}


void PwmChannel::setDuty(float duty)
{
  dutyCycle = duty;
  int dir = dutyCycle >= 0 ? 1 : -1;

  unsigned ot = unsigned(driver.getPeriod() * dutyCycle * dir);
  ot <?= driver.getPeriod() - 4 * transDelay;

  Interrupts masked;

  direction = dir;
  newOnTime = ot;
}
  

float PwmChannel::getDuty()
{
  Interrupts masked;

  return dutyCycle;
}


PwmChannel* PwmChannel::handler(int phase, unsigned nextCycle)
{
  unsigned period = driver.getPeriod();

  if (phase == 0)
  {
    onTime = newOnTime;		// pick up new setting synchronously

    if (onTime < period / 2)
      ocPwm.raiseAt(nextCycle - onTime);

    ocBrk.raiseAt(nextCycle + period + 2 * transDelay);
  }
  else
  {
    if (onTime >= period / 2)
      ocPwm.raiseAt(nextCycle + period - onTime);

    if (direction >= 0)
      ocDir.raiseAt(nextCycle + transDelay);
    else
      ocDir.dropAt(nextCycle + transDelay);
  }

  return next;
}


