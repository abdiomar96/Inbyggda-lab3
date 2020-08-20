/*
 * The following Assembly functions are provided to
 * create delayes of varied lengths.
 * Registers used: R24 and R18.
 *
 * Author:	Malek Abdul Sater & AbdiRahman Omar Ali
 *
 * Date:	2019-12-09
 */ 

;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros: 
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC RVAL
	CPI RVAL, 0		
	BRNE delay_micros
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R18, RVAL
loop_dms:
	LDI RVAL, 250
	RCALL delay_micros
	LDI RVAL, 250
	RCALL delay_micros
	LDI RVAL, 250
	RCALL delay_micros
	LDI RVAL, 250
	RCALL delay_micros
	DEC R18
	CPI R18, 0
	BRNE loop_dms		
	RET

;==============================================================================
; Delay of X s
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_1_s:
	LDI RVAL, 250
	RCALL delay_ms
	LDI RVAL, 250
	RCALL delay_ms
	LDI RVAL, 250
	RCALL delay_ms
	LDI RVAL, 250
	RCALL delay_ms
	RET