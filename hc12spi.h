// $Id: hc12spi.h,v 1.1 2003/12/20 17:28:58 cdavyduk Exp $

// hc12spi.h			   Copyright (C) 2003, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	68HC12 SPI Driver
//
//---------------------------------------------------------------------------

#ifndef HC12SPI_H
#define HC12SPI_H

#include "chipio.h"
#include "spi.h"


class HC12Spi : public Spi
{
public:
  HC12Spi(volatile spiport& s)
  : spi(s)
  {
    ddrs |= 0xE0;	// turn on SS, SCK, and MOSI outputs
    spi.spcr1 = spi.spe | spi.mstr | spi.cpha;
    spi.spdr = 0;
  }

  virtual ~HC12Spi()
  {
    spi.spcr1 = spi.cpha;
  }

private:
  virtual void put(void* data, int bits)
  {
    char* p = static_cast<char*>(data);
    
    for (int i = 0; i < bits / 8; ++i)
    {
      spi.spdr = *p++;
      while ((spi.spsr & spi.spif) == 0)
        ;
    }
  }

  virtual void get(void* data, int bits)
  {
    char* p = static_cast<char*>(data);
    
    for (int i = 0; i < bits / 8; ++i)
    {
      spi.spdr = 0;
      while ((spi.spsr & spi.spif) == 0)
        ;
      *p++ = spi.spdr;
    }
  }
  
  volatile spiport& spi;
};


#endif // HC12SPI_H

