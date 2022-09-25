.section .vectors
.global __vectors
.global __reset_handler
.global __null_handler

__vectors:
	jmp __reset_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler
	jmp __null_handler

__null_handler:
	rjmp __null_handler

__reset_handler:

	ldi ZL, 0x40		; PORTB.DIR
	ldi ZH, 0x00		;
	ldi r18, 0xFF
	st Z, r18

	ldi ZL, 0x40		; PORTB.OUT
	ldi ZH, 0x04		;
	ldi r18, 0xFF
	st Z, r18

	rjmp __reset_handler
