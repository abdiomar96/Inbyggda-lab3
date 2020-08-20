/*
 * Returns RVAL (R24), the value for a number 
 * on the numberpad provided from the laboration. 
 * Registers used: R24, R19 and R20.
 *  Created: 2019-12-09 
 *  Authors: Malek Abdul Sater & AbdiRahman Omar Ali
 */
;==============================================================================
;Converts input R24	to an ASCII character
; Parameters IN: R24(RVAL): contains number.
; OUT: R24: contains ASCII character.
;==============================================================================
ascii_converter:
	LDI ZH, high(map_table <<1) ;Initialize Z pointer
	LDI ZL, low(map_table <<1)
	ADD ZL, RVAL ;Add index
	LDI RVAL, 0x00
	ADC ZH, RVAL ;Add 0 to catch Carry, if present
	LPM RVAL, Z
	RET

read_keyboard:
	LDI R20, 0		; reset counter
scan_key:
	MOV R19, R20
	LSL R19
	LSL R19
	LSL R19
	LSL R19
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
	NOP
	NOP
	NOP
	NOP
	OUT PORTB, R19
	LDI RVAL, 6
	RCALL delay_ms
	
	SBIC PINE, 6
	RJMP return_key_val
	INC R20
	CPI R20, 12
	BRNE scan_key
	LDI R20, NO_KEY		; no key was pressed!

return_key_val:
	MOV RVAL, R20
	RCALL ascii_converter
	;RCALL lcd_write_chr
	RET