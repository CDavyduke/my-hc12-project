; Filename:		CRT0.S
; Author:		C.DAVYDUKE
; File Created:		03/09/11
; Last Modified:	03/10/08
; Description:		This file contains the code to set up the stack
;			and jump to CRT1.CC.
	public _start
_start	
	lds	#_stack_top	; set initial stack pointer
	movw	#0,2,-s		; terminate return chain
	movw	#0,2,-s		; terminate frame chain
	tfr	s,x		; set initial frame pointer
	jmp 	_crt1__Fv	; run crt1()
