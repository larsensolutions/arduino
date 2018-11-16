# Arduino
Different sketches for the arduino and other microcontrollers and IC's.

## General sketches
The purpose of these sketches is to learn the basics and be able to apply the stuff in my bigger projects! These are also the sketches that might be of interest to other people.

### [ButtonRead](https://github.com/larsensolutions/arduino/tree/master/ButtonRead) Using single 8 bit 74HC575 to read push button inputs 
Using a 74HC595 shift register to read button pushes

* [Thinkercad sketch](https://www.tinkercad.com/things/dOxVGoxMftm)

![Circuit diagram](ButtonRead/SN74HC595-ButtonInputReader.png?raw=true "Sketch")

### [ButtonReadChain](https://github.com/larsensolutions/arduino/tree/master/ButtonReadChain) Using several 8 bit 74HC575's to read push button inputs 
Using two 74HC595 shift registers to read button pushes. Code is scalable to read from a # of shift registers.

* [Thinkercad sketch](https://www.tinkercad.com/things/7BMBGhKhBrG)

![Circuit diagram](ButtonReadChain/SN74HC595-ButtonInputReaderChained.png?raw=true "Sketch")

### [LedFlasher](https://github.com/larsensolutions/arduino/tree/master/LedFlasher) Using a 8 bit 74HC575 to toggle some LED's
Using a 74HC595 shift registers to drive 3 LED's.

* [Thinkercad sketch](https://www.tinkercad.com/things/cHowXQvEdyA)

![Circuit diagram](LedFlasher/ledflasher.png?raw=true "Sketch")

## Non generic sketches
Very personalized and in progress stuff, and thus doesn't provide any value for other people.

### [RaspdusWifi](https://github.com/larsensolutions/arduino/tree/master/RaspdusWifi) ESP8266-07 Wifi chip, will serve as brain in the Raspdus controller project
Basically combines the stuff from the other sketches. In the end this will become a remote control that connects to my wifi at home that talks to my home automation API to control for instance lights.

## Resources

* Generate circuit diagrams: [Thinkercad](https://www.tinkercad.com)

## Contact

Erik Andreas Larsen – [@grizzifrog](https://twitter.com/grizzlifrog) – eriklarsen.post@gmail.com