// $Id: hc12ictlr.h,v 1.1 2003/11/06 05:27:26 cdavyduk Exp $

// hc12ictlr.h			   Copyright (C) 2002, Real-Time Systems Inc.
//------------------------------------------- All Rights Reserved -----------
//
//	68HC12 Interrupt Controller
//
//---------------------------------------------------------------------------

#ifndef HC12ICTLR_H
#define HC12ICTLR_H

#include "isr.h"


class HC12Ictlr : public Ictlr
{
public:
  HC12Ictlr();
  ~HC12Ictlr();

  enum Sources
  {
    isBdl,
    isAtd,
    isSc0,
    isSpi,
    isPai,
    isPao,
    isTof,
    isTc7,
    isTc6,
    isTc5,
    isTc4,
    isTc3,
    isTc2,
    isTc1,
    isTc0,
    isRti,
    isIrq,
    
    isNumSources
  };    

private:
  static void handlerTable() __attribute__ ((unused));
  static HC12Ictlr* theHC12Ictlr;
};


#endif // HC12ICTLR_H

