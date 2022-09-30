#ifndef ATTINY_CRT_H
#define ATTINY_CRT_H

void __interrupts_enable(void);
void __interrupts_disable(void);
void _exit(int unused);
void __sleep(void);

#endif
