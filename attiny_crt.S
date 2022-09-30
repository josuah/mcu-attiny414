#define zero        r1
#define SPL         0x3D
#define SPH         0x3E
#define SREG        0x3F

.macro .interrupt name
.global __vector_\name
__vector_\name:
    push    r1
    in      r1, SREG
    push    zero
    clr     zero
    push r18 $ push r19 $ push r20 $ push r21 $ push r22 $ push r23
    push r24 $ push r25 $ push r26 $ push r27 $ push r30 $ push r31
    call    __interrupt_\name
    pop r31 $ pop r30 $ pop r27 $ pop r26 $ pop r25 $ pop r24
    pop r23 $ pop r22 $ pop r21 $ pop r20 $ pop r19 $ pop r18
    pop     r1
    out     SREG, r1
    pop     r1
    reti
.endm

.section .vectors

.global __vectors
__vectors:
    rjmp __reset_handler             ; 0x00:
    rjmp __null_handler              ; 0x01: CRCSCAN_NMI
    rjmp __null_handler              ; 0x02: BOD_VLM
    rjmp __null_handler              ; 0x03: PORTA_PORT
    rjmp __null_handler              ; 0x04: PORTB_PORT
    rjmp __null_handler              ; 0x05: PORTC_PORT
    rjmp __null_handler              ; 0x06: RTC_CNT
    rjmp __vector_rtc_pit            ; 0x07: RTC_PIT
    rjmp __null_handler              ; 0x08: TCA0_OVF
    rjmp __null_handler              ; 0x09: TCA0_HUNF
    rjmp __null_handler              ; 0x0A: TCA0_CMP0
    rjmp __null_handler              ; 0x0B: TCA0_CMP1
    rjmp __null_handler              ; 0x0C: TCA0_CMP2
    rjmp __vector_tcb0_int           ; 0x0D: TCB0_INT
    rjmp __null_handler              ; 0x0E: TCD0_OVF
    rjmp __null_handler              ; 0x0F: TCD0_TRIG
    rjmp __null_handler              ; 0x10: AC0_AC
    rjmp __vector_adc0_resrdy        ; 0x11: ADC0_RESRDY
    rjmp __null_handler              ; 0x12: ADC0_WCOMP
    rjmp __null_handler              ; 0x13: TWI0_TWIS
    rjmp __null_handler              ; 0x14: TWI0_TWIM
    rjmp __null_handler              ; 0x15: SPI0_INT
    rjmp __null_handler              ; 0x16: USART0_RXC
    rjmp __vector_usart0_dre         ; 0x17: USART0_DRE
    rjmp __null_handler              ; 0x18: USART0_TXC
    rjmp __null_handler              ; 0x19: NVMCTRL_EE

.interrupt adc0_resrdy
.interrupt usart0_dre
.interrupt tcb0_int
.interrupt rtc_pit

.section .text

.global __reset_handler
__reset_handler:
    clr     zero
    ; copy data
    ldi     ZL, lo8(__data_load_start)
    ldi     ZH, hi8(__data_load_start)
    ldi     XL, lo8(__data_start)
    ldi     XH, hi8(__data_start)
    rjmp    1f
0:  lpm     r0, Z+
    st      X+, r0
1:  cpi     XL, lo8(__data_end)
    brne    0b
    cpi     XH, hi8(__data_end)
    brne    0b
    ; clear bss
    ldi     ZH, hi8(__bss_start)
    ldi     ZL, lo8(__bss_start)
    rjmp    1f
0:  st      Z+, zero
1:  cpi     ZL, lo8(__bss_end)
    brne    0b
    cpi     ZH, hi8(__bss_end)
    brne    0b
    ; ready to call C function
    call    main
0:  rjmp    0b

.global __null_handler
__null_handler:
0:  rjmp    0b

.global _exit
_exit:
0:  rjmp    0b

.global __interrupts_enable
__interrupts_enable:
    sei
    ret

.global __interrupts_disable
__interrupts_disable:
    cli
    ret

.global __sleep
__sleep:
    sleep
    ret
