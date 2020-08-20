/*
 * tarning.inc
 *
 *  Created: 2020-01-04 18:23:13
 *   Author: Malek Abdul Sater & Abdirahman Omar Ali
 */
tarning_prog_intro: 
	PRINTSTRING Str_welcome
	LDI RVAL, 250
	RCALL delay_ms
	RCALL delay_ms
	RCALL delay_ms
	RCALL delay_ms
	RCALL lcd_clear_display
/*
press_two:
	PRINTSTRING Str_press_two
	RCALL delay_1_s
	RCALL lcd_clear_display
	*/
	RJMP start_game

rolling_screen:
	RCALL lcd_clear_display
	PRINTSTRING Str_rolling
roll_dice:
	LDI R17, 6 ;dice have 6 values
test:
	NOP
	NOP
	RCALL read_keyboard ;key-value in RVAL
	CPI RVAL, ROLL_KEY
	BREQ roll ;yes, key 2 is still pressed
	RCALL lcd_clear_display
	PRINTSTRING Str_value
	RJMP return_dice;RET ;no, key is released
roll:
	DEC R17 ;start cycle count here
	BREQ roll_dice ;R16 is zero?, start agn at 6
	RJMP test ;no, keep rolling
	
return_dice:
	MOV RVAL, R17
	RCALL store_stat
	SUBI RVAL, -0x30
	RCALL lcd_write_chr
	RCALL delay_1_s
	CLR RVAL
	RJMP start_game
	
start_game:
	RCALL lcd_clear_display
	PRINTSTRING Str_press_two
	RCALL delay_1_s
start_game_1:
	RCALL read_keyboard
	CPI RVAL, NO_KEY
	BREQ start_game
	CPI rval, ROLL_KEY
	BREQ rolling_screen
	CPI RVAL, '3'
	BREQ r_show_stat
	CPI RVAL, '9'
	BREQ r_monitor
	CPI RVAL, '8'
	BREQ r_clear_stat
	RJMP start_game_1

r_show_stat:
	RCALL showstat
	RJMP start_game
r_monitor:
	RCALL monitor
	RJMP start_game
r_clear_stat:
	RCALL clearstat
	RCALL delay_1_s
	RJMP start_game
