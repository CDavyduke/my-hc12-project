// Filename:		APPCMDPROC.H
// Author:			C. DAVYDUKE
// File Created:	03/10/21
// Last Modified: 03/12/09
// Description:	This file contains the class definitions for the application command processor base class.

#ifndef __APPCMDPROC_H__
#define __APPCMDPROC_H__

#include "cmdproc.h"
#include "pwm.h"
#include "task.h"
#include "stddef.h"

class AppCmdProc : public CmdProc, public Task
{
  public:
    AppCmdProc( streambuf *, size_t, unsigned int, PwmChannel &, PwmChannel & );
    virtual void main();
  private:
    PwmChannel & rpChannel0;
    PwmChannel & rpChannel1;
};

#endif
