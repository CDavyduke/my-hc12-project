// Filename:        SETDUTYCMD.H
// Author:            C. DAVYDUKE
// File Created:    03/11/19
// Last Modified:  03/11/21
// Description:     This file contains the class definitions for the dump memory command.

#ifndef __SETDUTYCMD_H__
#define __SETDUTYCMD_H__
#include "cmdproc.h"
#include "stddef.h"
#include "pwm.h"

class SetDutyCmd : public Cmd
{
  public:
    SetDutyCmd( const char * name, PwmChannel & p )
    : Cmd( name ),
      rPwmChannel( p )
    {
    }

    virtual const char * parse( istream & is, ostream & os )
    {
      float dutyCycle;
			
      if( !( is >> dutyCycle ) )		// get start address in hex
        return "need duty cycle";

      os << flush;
      
      rPwmChannel.setDuty( dutyCycle );

      return 0;
    }

  private:
    PwmChannel & rPwmChannel;
};

#endif

