# Arduino and ESP scripts
Collection of different sketches for arduino and other microcontrollers (Like ESP8266)

### [ButtonRead](https://github.com/larsensolutions/arduino/tree/master/ButtonRead) Using single 8 bit 74HC575 to read button push inputs 
Using a 74HC595 shift register to read button pushes

![Circuit diagram](ButtonRead/SN74HC595-ButtonInputReader.png?raw=true "Sketch")

### [ButtonReadChain](https://github.com/larsensolutions/arduino/tree/master/ButtonReadChain) Using several 8 bit 74HC575's to read button push inputs 
Using two 74HC595 shift registers to read button pushes. Code is scalable to read from a # of shift registers.

![Circuit diagram](ButtonReadChain/SN74HC595-ButtonInputReaderChained.png?raw=true "Sketch")