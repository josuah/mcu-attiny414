CFLAGS += -Wall -Wextra -std=c99

OBJ += firmware.o
OBJ += attiny_crt.o
OBJ += attiny_adc.o
OBJ += attiny_usart.o
OBJ += attiny_tcb.o
OBJ += attiny_clkctrl.o
LIBS += -lgcc -lc

PYMCUPROG = pymcuprog -d attiny414 -t uart -u /dev/ttyUSB0
CC = avr-gcc -mmcu=attiny414
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy

all: firmware.hex

clean:
	rm -f *.o *.elf *.asm *.hex

ping:
	$(PYMCUPROG) ping

flash: firmware.hex
	$(PYMCUPROG) write -f firmware.hex --verify --erase

.SUFFIXES: .c .S .o .elf .hex

firmware.elf: $(OBJ)
	$(CC) $(LDFLAGS) -Wl,-Map=firmware.map,-Tattiny414.ld,--gc-sections -nostdlib -o $@ $(OBJ) $(LIBS)
	$(OBJDUMP) -z -D $@ >$*.asm

.c.o:
	$(CC) $(CFLAGS) -ffunction-sections -fdata-sections -c -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -D__ASSEMBLY__ -c -o $@ $<

.elf.hex:
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
