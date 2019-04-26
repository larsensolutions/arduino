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

#### Components
* 1 x ESP8266-07 wifi module
* 1 x LD33V 3.3V regulator
* 4 x 74HC595 shift registers
* 1 x 0.1uF ceramic capacitator
* 1 x 10uF polarized capacitator
* 1 x 10K resistor
* 16 x 470 ohm resistors
* 16 x zener diodes
* 6 x six-position male pin connector
* 3 x two-position male pin connectors
* 1 x two-position screw terminal

* [Tinkercad sketch](https://www.tinkercad.com/things/98GHd9cAQSt)

![Rough sketch of circuit diagram](RaspdusWifi/images/raspdus-wifi-controller-circuit.jpg?raw=true "Rough sketch of circuit diagram")
![PCB circuit using Fritzing software](RaspdusWifi/images/raspdus-wifi-controller-circuit-fritzing.jpg?raw=true "PCB circuit")

#### Ordered the PCB print from [PCBway.com](http://pcbway.com), here is what it looked like

![PCB circuit without components](RaspdusWifi/images/raspdus-wifi-controller-circuit-no-components.jpg?raw=true "PCB circuit without components")

#### [Video on youtube showing the process of soldering](https://youtu.be/xztIZzjC5tE)

![PCB circuit with components](RaspdusWifi/images/raspdus-wifi-controller-circuit-with-components.jpg?raw=true "PCB circuit with components")

#### Final prototype results

![Box complete](RaspdusWifi/images/raspdus-box-complete.jpg?raw=true "Box complete")

#### Prototype build in progress

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

* Generate circuit diagrams (very simple ones) and 3D prints: [Tinkercad](https://www.tinkercad.com)
* Generate circuit diagrams [Fritzing](http://fritzing.org/home/)
* Order PCB prototype boards [PCBway](https://www.pcbway.com)

### [Motor](https://github.com/larsensolutions/arduino/tree/master/Motor) Under development. ROV control
Under development. Should control 3 ESC's, 1 servo and a couple of relays to control lights.

### [MotorCalibration](https://github.com/larsensolutions/arduino/tree/master/MotorCalibration) Under development. ESC calibration script
ESC calibration script

## Contact

Erik Andreas Larsen – [@grizzifrog](https://twitter.com/grizzlifrog) – eriklarsen.post@gmail.com

## Board config "AllFeatures" for the ESP8266-07

```js
{
    "board": "esp8266:esp8266:generic",
    "configuration": "xtal=80,vt=flash,exception=disabled,ResetMethod=ck,CrystalFreq=26,FlashFreq=40,FlashMode=dout,eesz=1M64,led=2,ip=lm2f,dbg=Disabled,lvl=None____,wipe=none,baud=115200",
    "sketch": "AllFeatures\\AllFeatures.ino",
    "port": "COM4",
    "output": "../ArduinoOutput"
}
```