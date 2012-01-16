// $Id: pwmdriver.h,v 1.1 2003/11/06 05:27:26 cdavyduk Exp $

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


class PwmDriver : public Isr
{
public:
  PwmDriver(Ictlr& ic, unsigned period);

protected:
  virtual void handler();
  
private:
  unsigned int period;

  OutputCompare ocTick;
};


#endif // PWM_H

