MCU		= atmega328p
SRC		= main
PORT		= /dev/spidev0.0

all:
	avr-gcc -Os -mmcu=$(MCU) -I/home/svrle/buzzwire/ -I/usr/lib/avr/include/ -c $(SRC).c
	avr-gcc -mmcu=$(MCU) -o $(SRC).elf $(SRC).o
	avr-objcopy -j .text -j .data -O ihex $(SRC).elf $(SRC).hex
	avr-size --mcu=$(MCU) -C $(SRC).elf
	sudo avrdude -P $(PORT) -c linuxgpio -p $(MCU) -U flash:w:$(SRC).hex

i:
	sudo avrdude -p $(MCU) -c linuxgpio -v

p:
	sudo avrdude -P $(PORT) -c linuxgpio -p $(MCU) -U flash:w:$(SRC).hex

er:
	sudo avrdude -p $(MCU) -c linuxgpio -U eeprom:r:-:h

c:
	rm -rf $(SRC).o
	rm -rf $(SRC).elf
	rm -rf $(SRC).hex
