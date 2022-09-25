OBJ = firmware.o

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
	$(PYMCUPROG) write -f firmware.hex

.SUFFIXES: .c .S .o .elf .asm .hex

firmware.elf: $(OBJ)
	$(CC) $(LDFLAGS) -Wl,-Map=firmware.map -Wl,--gc-sections -nostdlib -o $@ $(OBJ) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -ffunction-sections -fdata-sections -c -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -D__ASSEMBLY__ -c -o $@ $<

.elf.asm:
	$(OBJDUMP) -z -D $< >$@

.elf.hex:
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
