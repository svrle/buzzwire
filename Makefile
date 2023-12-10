MCU		= atmega328p
SRC		= blink
PORT		= /dev/spidev0.0

all:
	avr-gcc -Os -mmcu=$(MCU) -I/usr/lib/avr/include/ -c $(SRC).c
	avr-gcc -mmcu=$(MCU) -o $(SRC).elf $(SRC).o
	avr-objcopy -j .text -j .data -O ihex $(SRC).elf $(SRC).hex

s:
	avr-size --mcu=$(MCU) -C $(SRC).elf

i:
	avrdude -p $(MCU) -c linuxgpio -v

p:
	avrdude -P $(PORT) -c linuxgpio -p $(MCU) -U flash:w:$(SRC).hex

c:
	rm -rf $(SRC).o
	rm -rf $(SRC).elf
	rm -rf $(SRC).hex
