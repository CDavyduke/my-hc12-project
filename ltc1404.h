// $Id: ltc1404.h,v 1.2 2003/12/20 22:54:19 cdavyduk Exp $

// ltc1404.h			   Copyright (C) 2003, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	LTC1404 A/D Converter Driver
//
//---------------------------------------------------------------------------

#ifndef LTC1404_H
#define LTC1404_H

#include "chipio.h"
#include "spi.h"
#include "task.h"
#include "interrupts.h"

// Need a mask to configure SCK and SS as outputs.
const unsigned int selMask = 0xC0;

class Ltc1404 : public Task
{
public:
  Ltc1404( size_t stackSize, unsigned int priority, Spi & s, int t )
  : Task( stackSize, priority ),
    spi( s ),
    time( t )
  {
    Interrupts masked;
    
    ddrs |= selMask;

    ddrdlc |= ( 1 << 6 );
    portdlc &= ~(1 << 6 );
    fork();
  }

  ~Ltc1404()
  {
    Interrupts masked;
    
    ddrs &= ~selMask;
  }
  
protected:
  void main();

private:
  class Ltc1404SpiUser : public SpiUser
  {
  public:
    Ltc1404SpiUser(Spi& spi)
    : SpiUser(spi)
    {
      Interrupts masked;
      
      ports |= selMask;
    }

    ~Ltc1404SpiUser()
    {
      Interrupts masked;
      
      ports &= ~selMask;
    }

    operator int()
    {
      int buf;
      get(&buf, sizeof(buf) * 8);
      return buf;
    }
  };

  Spi& spi;
  int time;
};


#endif // LTC1404_H

