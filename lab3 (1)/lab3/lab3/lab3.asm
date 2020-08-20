; lab3.asm
; 
; Main program for a dice-thrower. Every number generated is stored and
; statistics can be shown then cleared.
;
; Created: 2020-01-20
; Author : Malek Abdul Sater & Abdirahman Omar Ali
;

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	.EQU NO_KEY		= 0x0F
	.EQU ROLL_KEY	= '2'

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
	.INCLUDE "delay.inc"
	.INCLUDE "lcd.inc"
	.INCLUDE "keyboard.inc"
	.INCLUDE "tarning.inc"
	.INCLUDE "stats.inc"
	.INCLUDE "monitor.inc"
	.INCLUDE "stat_data.inc"
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	; Set stack pointer to point at the end of RAM.
	LDI R16, LOW(RAMEND)
	OUT SPL, R16
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	; Initialize pins
	RCALL init_pins
	; Jump to main part of program
	CALL lcd_init
	CALL init_monitor
	CALL init_stat
	LDI R24, 0x0C
	RCALL lcd_write_instr
	map_table: 
		.DB "147*2580369#"
	
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
	LDI TEMP, 0xFF
	OUT DDRD, R16
	OUT DDRF, TEMP
	OUT DDRB, TEMP
	LDI TEMP, 0x00
	OUT DDRE, TEMP
	RET

;==============================================================================
; Reads numberpad buttons and assigns values from the ASCII-table
; Parameters IN: R24(RVAL): contains number.
; R17: used for comparing values.
; OUT: R24: contains ASCII character.
;==============================================================================

keep_searching:
	CALL read_keyboard
	CPI RVAL, NO_KEY
	BREQ keep_searching
	CPI RVAL, 10
	BREQ letter_aorb
	CPI RVAL, 11
	BREQ letter_aorb
	MOV R17, RVAL
ascii_shift:
	SUBI RVAL, -48
	RCALL lcd_write_chr
	RCALL delay_ms
same_button:
	RCALL read_keyboard
	CP RVAL, R17
	BREQ same_button
	RJMP keep_searching
	NOP
	NOP
	RJMP main
letter_aorb:
	SUBI RVAL, -7
	RJMP ascii_shift

;==============================================================================
; Main part of program
;==============================================================================
main:
	RJMP tarning_prog_intro
	RJMP main