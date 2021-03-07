CFLAGS := -Wall -Os -DF_CPU=7372800 -mmcu=atmega8

SOURCES := $(shell find -name "*.c")
OBJECTS := $(SOURCES:%.c=%.o)


all: $(OBJECTS)
	avr-gcc $(CFLAGS) -o main.elf $(OBJECTS)
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --mcu=atmega8 -C main.elf

%.o: %.c
	avr-gcc $(CFLAGS) -c $< -o $@


upload: all
	avrdude -p atmega8 -c usbasp -P usb -B 10 -U flash:w:main.hex

fuses:
	avrdude -p atmega8 -c usbasp -P usb -B 10 -U lfuse:w:0xfd:m -U hfuse:w:0xc9:m


clean:
	rm -f *.o main.elf main.hex

tools:
	sudo apt-get install gcc-avr avr-libc uisp avrdude python3 python3-serial

