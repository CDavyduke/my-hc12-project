// Filename:      SPI.H
// Author:        C. DAVYDUKE
// File Created:  03/12/17
// Last Modified: 03/12/20
// Description:   This file contains the class definitions for the Spi base class.

#ifndef __SPI_H__
#define __SPI_H__

#include "mutex.h"

class Spi  // body class
{
  public:
    Spi();
    virtual ~Spi();
  private:
    virtual void get( void *, int )
    {
    }
    virtual void put( void *, int )
    {
    }
    void open()
    {
      mutex.acquire();
    }
    void close()
    {
      mutex.release();
    }
    Mutex mutex;
    friend class SpiUser;
};

class SpiUser  // handle class
{
  public:
    SpiUser( Spi & s )
    : spi( s )
    {
      spi.open();
    }
    ~SpiUser()
    {
      spi.close();
    }
    void get( void * p, int b ) // reflect operation to body class.
    {
      spi.get( p, b );
    }
    void put( void * p, int b ) // reflect operation to body class.
    {
      spi.put( p, b );
    }
  private:
    Spi & spi;
};

#endif

