# buzzwire
Old fashion game with networking and multiplayer


## Releases:

v1 - Basic reaction on wire, when wire is connected led diode would go On and have buffer of 250ms in case of flapping main wire

## Setup Programmer
- [Raspberry Pi 3](setup/rpi.md)

## Preparing FUSE on MCU
External crystal at 16MHz
```bash
avrdude -p atmega328p -c usbasp -U lfuse:w:0xdf:m -U hfuse:w:0xDF:m -U efuse:w:0xF9:m -U lock:w:0xFF:m 
```
Reference: https://www.pocketmagic.net/how-to-set-the-avr-fusebits/

