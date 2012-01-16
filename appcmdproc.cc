// Filename:		APPCMDPROC.CC
// Author:			C. DAVYDUKE
// File Created:	03/10/21
// Last Modified: 03/12/09
// Description:	This file contains the class methods for the application command processor base class.

#include "appcmdproc.h"
#include "cmdproc.h"
#include "hellocmd.h"
#include "dumpmemcmd.h"
#include "setdutycmd.h"
#include "getdutycmd.h"
#include "pwm.h"
#include "stddef.h"
#include "task.h"

AppCmdProc::AppCmdProc
( 
  streambuf * sbuf, 
  size_t ss, unsigned int p, 
  PwmChannel & rp0, PwmChannel & rp1 
)
: CmdProc( sbuf, "TEC>" ),
  Task( ss, p ),
  rpChannel0( rp0 ),
  rpChannel1( rp1 )
{
  fork();
}

void AppCmdProc::main()
{
  Cmd * menu[] =
  {
    new HelloCmd( "hello" ),
    new DumpMemCmd( "dump" ),
    new SetDutyCmd( "settecduty" , rpChannel0 ),
    new SetDutyCmd( "setlsrduty", rpChannel1 ),
    new GetDutyCmd( "gettecduty", rpChannel0 ),
    new GetDutyCmd( "getlsrduty", rpChannel1 ),
    0
  };

  present( menu );

  for( Cmd * * cmd = & menu[0]; *cmd; cmd++ )
    delete * cmd;
}
