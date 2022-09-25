#define zero r1


.section .vectors
.global __vectors

__vectors:
	jmp __reset_handler
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;
	jmp __null_handler ;


.section .text
.global	__reset_handler
.global	__null_handler
.global	__stop_program

__null_handler:
__stop_program:
 0:
 	rjmp 0b

__reset_handler:
	clr zero

__copy_data:
	ldi ZL, lo8(__data_load_start)
	ldi ZH, hi8(__data_load_start)
	ldi XL, lo8(__data_start)
	ldi XH, hi8(__data_start)

	rjmp 1f
 0:
	; Load a byte from Program Memory to the RAM
	lpm r0, Z+
	st X+, r0
 1:
	; done yet?
	cpi XL, lo8(__data_end)
	brne 0b
	cpi XH, hi8(__data_end)
	brne 0b

__clear_bss:
	ldi ZH, hi8(__bss_start)
	ldi ZL, lo8(__bss_start)

	rjmp 1f
 0:
	/* fill the stack with one more 0 */
	st Z+, zero
 1:
	/* done yet? */
	cpi ZL, lo8(__bss_end)
	brne 0b
	cpi ZH, hi8(__bss_end)
	brne 0b

__call_main:
	call main
 0:
	rjmp 0b
