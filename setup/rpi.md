# Raspberry Pi setup for programming

## Librarys and packages

- Installing compailer and needed tools
```bash
sudo apt-get install gcc-avr git-core binutils-avr avr-libc avrdude avrdude-doc 
```

## Pin connection
```
  Rpi3            ATMega328P
MOSI(GPIO10)-----PB3(MOSI) 
MISO(GPIO09)-----PB4(MISO)
SCLK(GPIO11)-----PB5(SCK)
Ground-----------GND
GPIO23-----------PC6(RESET)
```
## Configuring `avrdude`

Edit `/etc/avrdude.conf` file and change it as:
```
#
# PROGRAMMER DEFINITIONS
#

# http://wiring.org.co/
# Basically STK500v2 protocol, with some glue to trigger the
# bootloader.
programmer
  id    = "linuxgpio";
  desc  = "Usethe linux sysfs interface";
  type  = "linuxgpio";
  reset = 23;
  sck   = 11;
  mosi  = 10;
  miso  = 9;
;
```

## Uploading(burning) program to MCU

- Upload `FILE.hex`
```bash
sudo avrdude -P /dev/spidev0.0 -c linuxgpio -p atmega328p -U flash:w:FILE.hex
```
