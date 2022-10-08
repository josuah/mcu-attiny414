#define temp        r0
#define zero        r1
#define SPL         0x3D
#define SPH         0x3E
#define SREG        0x3F
#define CCP         0x34
#define CCP_IOREG   0xD8

.macro .interrupt onoff, vector, interrupt
.if \onoff == 1
\vector:
    push    r1
    in      r1, SREG
    push    zero
    clr     zero
    push r18 $ push r19 $ push r20 $ push r21 $ push r22 $ push r23
    push r24 $ push r25 $ push r26 $ push r27 $ push r30 $ push r31
    call    \interrupt
    pop r31 $ pop r30 $ pop r27 $ pop r26 $ pop r25 $ pop r24
    pop r23 $ pop r22 $ pop r21 $ pop r20 $ pop r19 $ pop r18
    pop     r1
    out     SREG, r1
    pop     r1
    reti
.else
.weakref \vector, __null_handler
.endif
.endm

.section .vectors

__vectors:
    rjmp __reset_handler                ; 0x00
    rjmp __vector_1                     ; 0x01
    rjmp __vector_2                     ; 0x02
    rjmp __vector_3                     ; 0x03
    rjmp __vector_4                     ; 0x04
    rjmp __vector_5                     ; 0x05
    rjmp __vector_6                     ; 0x06
    rjmp __vector_7                     ; 0x07
    rjmp __vector_8                     ; 0x08
    rjmp __vector_9                     ; 0x09
    rjmp __vector_10                    ; 0x0A
    rjmp __vector_11                    ; 0x0B
    rjmp __vector_12                    ; 0x0C
    rjmp __vector_13                    ; 0x0D
    rjmp __vector_14                    ; 0x0E
    rjmp __vector_15                    ; 0x0F
    rjmp __vector_16                    ; 0x10
    rjmp __vector_17                    ; 0x11
    rjmp __vector_18                    ; 0x12
    rjmp __vector_19                    ; 0x13
    rjmp __vector_20                    ; 0x14
    rjmp __vector_21                    ; 0x15
    rjmp __vector_22                    ; 0x16
    rjmp __vector_23                    ; 0x17
    rjmp __vector_24                    ; 0x18
    rjmp __vector_25                    ; 0x17

.interrupt 0, __vector_1,  __interrupt_crcscan_nmi
.interrupt 0, __vector_2,  __interrupt_bod_vlm
.interrupt 0, __vector_3,  __interrupt_porta_port
.interrupt 0, __vector_4,  __interrupt_portb_port
.interrupt 0, __vector_5,  __interrupt_portc_port
.interrupt 0, __vector_6,  __interrupt_rtc_cnt
.interrupt 0, __vector_7,  __interrupt_rtc_pit
.interrupt 0, __vector_8,  __interrupt_tca0_ovf
.interrupt 0, __vector_9,  __interrupt_tca0_hunf
.interrupt 0, __vector_10, __interrupt_tca0_cmp0
.interrupt 0, __vector_11, __interrupt_tca0_cmp1
.interrupt 0, __vector_12, __interrupt_tca0_cmp2
.interrupt 0, __vector_13, __interrupt_tcb0_int
.interrupt 0, __vector_14, __interrupt_tcd0_ovf
.interrupt 0, __vector_15, __interrupt_tcd0_trig
.interrupt 0, __vector_16, __interrupt_ac0_ac
.interrupt 0, __vector_17, __interrupt_adc0_resrdy
.interrupt 0, __vector_18, __interrupt_adc0_wcomp
.interrupt 0, __vector_19, __interrupt_twi0_twis
.interrupt 0, __vector_20, __interrupt_twi0_twim
.interrupt 1, __vector_21, __interrupt_spi0_int
.interrupt 0, __vector_22, __interrupt_usart0_rxc
.interrupt 0, __vector_23, __interrupt_usart0_dre
.interrupt 0, __vector_24, __interrupt_usart0_txc
.interrupt 0, __vector_25, __interrupt_nvmctrl_ee

.section .text

.global __reset_handler
__reset_handler:
    clr     zero
__copy_data:
    ldi     ZL, lo8(__data_load_start)
    ldi     ZH, hi8(__data_load_start)
    ldi     XL, lo8(__data_start)
    ldi     XH, hi8(__data_start)
    rjmp    1f
0:  lpm     temp, Z+
    st      X+, r0
1:  cpi     XL, lo8(__data_end)
    brne    0b
    cpi     XH, hi8(__data_end)
    brne    0b
__clear_bss:
    ldi     ZH, hi8(__bss_start)
    ldi     ZL, lo8(__bss_start)
    rjmp    1f
0:  st      Z+, zero
1:  cpi     ZL, lo8(__bss_end)
    brne    0b
    cpi     ZH, hi8(__bss_end)
    brne    0b
__call_main:
    call    main
0:  rjmp    0b

__null_handler:
0:  rjmp    0b

; r24   (uint8_t *) Pointer to the register to write to.
; r22   (uint8_t)   Value to insert
.global __protected_write
__protected_write:
    movw    Z, r24
    ldi     r18, CCP_IOREG
    out     CCP, r18
    st      Z, r22
    ret
