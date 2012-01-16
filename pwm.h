// $Id: pwm.h,v 1.1 2003/11/06 05:27:26 cdavyduk Exp $

// pwm.h			   Copyright (C) 2003, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	PWM Driver
//
//---------------------------------------------------------------------------

#ifndef PWM_H
#define PWM_H

#include "isr.h"
#include "outputcompare.h"


class PwmChannel
{
public:
  PwmChannel(class PwmDriver& driver, int chanNum);

  void setDuty(float duty);
  float getDuty();

private:
  PwmChannel* handler(int phase, unsigned nextCycle);

  friend class PwmDriver;

private:  
  PwmChannel* next;
  class PwmDriver& driver;
  
  float dutyCycle;
  int direction;
  unsigned newOnTime;
  unsigned onTime;
  
  OutputCompare ocDir;
  OutputCompare ocPwm;
  OutputCompare ocBrk;
};


class PwmDriver : public Isr
{
public:
  PwmDriver(Ictlr& ic, unsigned period);

protected:
  virtual void handler();
  
private:
  PwmChannel* attach(PwmChannel* chan);

  unsigned getPeriod() const
  {
    return period;
  }

  friend class PwmChannel;
  
private:    
  PwmChannel* first;
  const unsigned period;

  int phase;

  OutputCompare ocTick;
  OutputCompare ocOff;
};


#endif // PWM_H

