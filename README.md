# Simple EEPROM Programmer



## Table of Contents
 - [Project](#project)
 - [Dependencies](#dependencies)
 - [Make](#make)
 - [Flash](#flash)
 - [PCB](#pcb)
 - [Enclosure](#enclosure)
 - [License](#license)

## Project

I created this programmer for my personal Z80 project. Since commerical programmers are fairly expensive I created my own simple programmer. It is nothing fancy and just supports a single family of EEPROMs. It does not have support for a higher programming voltage and is limited for +5V EEPROMs.

This simple programmer supports following EEPROMs:
 - 28c64 (8k)
 - 28c256 (32k)


## Dependencies

To compile the code you need to have following tools installed:
 - avr-gcc (with avr-libs)
 - avrdude
 - uisp

The programmer flash tool uses [Python3](https://www.python.org/) and [pySerial](https://pyserial.readthedocs.io/en/latest/pyserial.html):
 - python3
 - python3-serial

The Makefile contains a command to install everything needed
```
cd code
sudo make tools
```


## Make

To compile the ATmega code execute following in the project root folder:
```
cd code
make
```

To flash the compiled code to the programmer *connect the ISP-Programmer* and execute:
```
make fuses
make upload
```


## Flash

To flash your binary file to the EEPROM inserted type:
```
cd code
chmod +x eeprom.py
./eeprom.py -e -o -p /dev/ttyACM0 -b 115200 -w <binaryfile.bin>
```

For more information:
```
./eeprom.py -h
```


## PCB

Note: The pcb is designed so that the top layer represents jumpers. The vias are large enough to stick a wire through.

For the schematic and pcb layout I used [KiCad](https://kicad.org/), a very awsome open source EDA.

The clearances and spaces are designed for diy home etching. Nothing really fancy.

![Alt text](pictures/pcb_soldered.jpg?raw=true "PCB Picture")


## Enclosure

The very simple, easy and fast to print enclosure consists of two parts which sandwhich the pcb. Needed are just *4x M3,5x12mm* wood screws to assemble the enclosure.

![Alt text](pictures/case.jpg?raw=true "Case Picture")


## License

[MIT](LICENSE) Jannik Kreucher
