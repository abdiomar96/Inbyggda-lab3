 /* ---------------------------------------------------
Space in the RAM to save the results from dice throws.
The following functions are provided:
store_stat (R24 contains the dice value)
The function will increment the
Total number of throws and the
number of throws with results equals R24.
get_stat (R24 gives the value for which the
result is retrieved. If R24 = 0, the
total number of throws shall be returned.
The result is returned in R24.
clear_stat (no parameters in nor out)
Clears all data.
--------------------------------------------------------*/
.DSEG ; The following applies to the RAM:
.ORG 0x100 ; Set starting
; address of data
; segment to 0x100
counters_size: 
	.BYTE 7 ;<skapa så mycket plats som behövs.Antag att max värde per lagrad variabel är 255>
.CSEG
store_stat:
	LDI XH, HIGH(counters_size)
	LDI XL, LOW(counters_size)

	LD R19, X
	INC R19
	ST X, R19

	ADD XL, R17
	LD R17, X
	INC R17
	ST X, R17
	RET
get_stat:
	LDI XH, HIGH(counters_size)
	LDI XL, LOW(counters_size)
	ADD XL, RVAL
	LDI RVAL, 0
	ADC XH, RVAL
	LD RVAL, X
	RET
clear_stat:
	LDI R16, 0
	STS counters_size, TEMP
	STS counters_size+1, TEMP
	STS counters_size+2, TEMP
	STS counters_size+3, TEMP
	STS counters_size+4, TEMP
	STS counters_size+5, TEMP
	STS counters_size+6, TEMP
	RET