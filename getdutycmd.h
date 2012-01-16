// Filename:        GETDUTYCMD.H
// Author:            C. DAVYDUKE
// File Created:    03/11/21
// Last Modified:  03/11/21
// Description:     This file contains the class definitions for the dump memory command.

#ifndef __GETDUTYCMD_H__
#define __GETDUTYCMD_H__
#include "cmdproc.h"
#include "stddef.h"
#include "pwm.h"

class GetDutyCmd : public Cmd
{
  public:
    GetDutyCmd( const char * name, PwmChannel & p )
    : Cmd( name ),
      rPwmChannel( p )
    {
    }

    virtual const char * parse( istream &, ostream & os )
    {
      float dutyCycle;
      
      dutyCycle = rPwmChannel.getDuty( );

      os << endl << dutyCycle << flush;

      return 0;
    }

  private:
    PwmChannel & rPwmChannel;
};

#endif

