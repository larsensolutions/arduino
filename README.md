# Arduino
Different sketches for the arduino and other microcontrollers and IC's.

## Sketches
The purpose of most of these sketches is to learn the basics and be able to apply the stuff in my bigger projects! (Also included here)

* [Video on twitter demonstrating the "Raspdus box" made from this basic stuff](https://twitter.com/grizzlifrog/status/1070663566863290368)

### [ButtonRead](https://github.com/larsensolutions/arduino/tree/master/ButtonRead) Using single 8 bit 74HC575 to read push button inputs 
Using a 74HC595 shift register to read button pushes.

* [Tinkercad sketch](https://www.tinkercad.com/things/dOxVGoxMftm)

![Circuit diagram](ButtonRead/SN74HC595-ButtonInputReader.png?raw=true "Sketch")

### [ButtonReadChain](https://github.com/larsensolutions/arduino/tree/master/ButtonReadChain) Using several 8 bit 74HC575's to read push button inputs 
Using two 74HC595 shift registers to read button pushes. Code is scalable to read from a # of shift registers.

* [Tinkercad sketch](https://www.tinkercad.com/things/7BMBGhKhBrG)

![Circuit diagram](ButtonReadChain/SN74HC595-ButtonInputReaderChained.png?raw=true "Sketch")
![Implemented](ButtonReadChain/ButtonReadChain.jpg?raw=true "Implemented")

### [LedFlasher](https://github.com/larsensolutions/arduino/tree/master/LedFlasher) Using a 8 bit 74HC575 to toggle some LED's
Using a 74HC595 shift registers to drive 3 LED's.

* [Tinkercad sketch](https://www.tinkercad.com/things/cHowXQvEdyA)

![Circuit diagram](LedFlasher/ledflasher.png?raw=true "Sketch")

### [WebSocket](https://github.com/larsensolutions/arduino/tree/master/WebSocket) Using Websocket data to control LED status
Using a 74HC595 shift registers to drive LED status using data received from Websocket connection.

### [RaspdusWifi](https://github.com/larsensolutions/arduino/tree/master/RaspdusWifi) ESP8266-07 Wifi chip, will serve as brain in the Raspdus controller project
Basically combines the stuff from the other sketches. This is a remote control that connects to my wifi at home that talks to my home automation API to control the lights!

* [Tinkercad sketch](https://www.tinkercad.com/things/98GHd9cAQSt)

![Rough sketch of circuit diagram](RaspdusWifi/images/raspdus-wifi-controller-circuit.jpg?raw=true "Rough sketch of circuit diagram")

#### Final results

![Box complete](RaspdusWifi/images/raspdus-box-complete.jpg?raw=true "Box complete")

### Build in progress

![Box knobs](RaspdusWifi/images/raspdus-box-knobs.jpg?raw=true "Box knobs")
![Box prints](RaspdusWifi/images/raspdus-box-prints.jpg?raw=true "Box prints")
![Box wiring](RaspdusWifi/images/raspdus-box-wiring.jpg?raw=true "Box wiring")

[Video on twitter demonstrating the Raspdus box](https://twitter.com/grizzlifrog/status/1070663566863290368)

#### Custom 3D prints source files
* The box (print coloured parts separately) [Tinkercad 3D print](https://www.tinkercad.com/things/5O3gAvxATRC/edit?sharecode=LnFBwAcFzZKmgHHJWiTbrchXy2RChrDAEr17kh_O0ms=)
* The apartment [Tinkercad 3D print](https://www.tinkercad.com/things/06itOJWX7F3/edit?sharecode=p6LfuG1Tc5tmdaZJKfttCCOc3zg3f6xt6FtNrXc_VN0=)
* Logo and labels [Tinkercad 3D print](https://www.tinkercad.com/things/jhPKKVwyEU6-raspdus-box-logo-and-labels/edit?sharecode=u3jyjOwCSqnDHdXntYfT9-1s8Q0ZC1yVMoiltZoRI98=)
* All the other little things was found on [Thingiverse](https://www.thingiverse.com/)
* All .gx files are located here [.gx print files](https://github.com/larsensolutions/arduino/tree/master/RaspdusWifi/prints)

## Resources

* Generate circuit diagrams adn 3D prints: [Tinkercad](https://www.tinkercad.com)

## Contact

Erik Andreas Larsen – [@grizzifrog](https://twitter.com/grizzlifrog) – eriklarsen.post@gmail.com