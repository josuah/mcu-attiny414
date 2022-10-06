CFLAGS += -Wall -Wextra -Wconversion -Wmissing-prototypes -Wno-array-bounds
CFLAGS += -std=c99 -pedantic
CFLAGS += -Os
# Comment to enable UART debugging.
CFLAGS += -DNDEBUG

PYMCUPROG = pymcuprog -d attiny202 -t uart -u /dev/ttyUSB0
CC = avr-gcc -mmcu=attiny202
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy

OBJ += firmware.o
OBJ += attiny_adc.o
OBJ += attiny_clkctrl.o
OBJ += attiny_crt.o
OBJ += attiny_rtc.o
OBJ += attiny_slpctrl.o
OBJ += attiny_tcb.o
OBJ += attiny_usart.o
OBJ += attiny_vref.o
OBJ += put.o
LIBS += -lgcc -lc

all: firmware.hex

clean:
	rm -f *.o *.elf *.asm *.hex

ping:
	$(PYMCUPROG) ping

flash: firmware.hex
	$(PYMCUPROG) write -f firmware.hex --verify --erase

firmware.elf: $(OBJ)
	$(CC) $(LDFLAGS) -Wl,-Map=firmware.map,--gc-sections -nostdlib -o $@ $(OBJ) $(LIBS)
	$(OBJDUMP) -z -D $@ >$*.asm

$(OBJ): Makefile *.h

.SUFFIXES: .c .S .o .elf .hex

.c.o:
	$(CC) $(CFLAGS) -ffunction-sections -fdata-sections -c -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -D__ASSEMBLY__ -c -o $@ $<

.elf.hex:
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
