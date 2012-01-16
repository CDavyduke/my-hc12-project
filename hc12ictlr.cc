// $Id: hc12ictlr.cc,v 1.1 2003/11/06 05:27:53 cdavyduk Exp $

// hc12ictlr.cc			   Copyright (C) 2002, Real-Time Systems Inc.
//------------------------------------------- All Rights Reserved -----------
//
//	68HC12 Interrupt Controller
//
//---------------------------------------------------------------------------

#include "chipio.h"		// DEBUG
#include "hc12ictlr.h"


HC12Ictlr* HC12Ictlr::theHC12Ictlr;


HC12Ictlr::HC12Ictlr()
: Ictlr(isNumSources)
{
  theHC12Ictlr = this;
  ddrdlc |= (1 << 3);		// DEBUG
}


HC12Ictlr::~HC12Ictlr()
{
  theHC12Ictlr = 0;
}


void HC12Ictlr::handlerTable()
{

#define	vsr(source)							\
  asm("		public	vsr%c0"	: : "i" (HC12Ictlr::source)	);	\
  asm("\nvsr%c0"		: : "i" (HC12Ictlr::source)	);	\
  portdlc |= (1 << 3);			/* DEBUG */			\
  theHC12Ictlr->runHandler(source);					\
  portdlc &= ~(1 << 3);			/* DEBUG */			\
  asm("rti");

  vsr(isBdl);
  vsr(isAtd);
  vsr(isSc0);
  vsr(isSpi);
  vsr(isPai);
  vsr(isPao);
  vsr(isTof);
  vsr(isTc7);
  vsr(isTc6);
  vsr(isTc5);
  vsr(isTc4);
  vsr(isTc3);
  vsr(isTc2);
  vsr(isTc1);
  vsr(isTc0);
  vsr(isRti);
  vsr(isIrq);
};

