# Arduino
Different sketches for the arduino and other microcontrollers and IC's.

## Sketches
The purpose of most of these sketches is to learn the basics and be able to apply the stuff in my bigger projects!

### [ButtonRead](https://github.com/larsensolutions/arduino/tree/master/ButtonRead) Using single 8 bit 74HC575 to read push button inputs 
Using a 74HC595 shift register to read button pushes.

* [Thinkercad sketch](https://www.tinkercad.com/things/dOxVGoxMftm)

![Circuit diagram](ButtonRead/SN74HC595-ButtonInputReader.png?raw=true "Sketch")

### [ButtonReadChain](https://github.com/larsensolutions/arduino/tree/master/ButtonReadChain) Using several 8 bit 74HC575's to read push button inputs 
Using two 74HC595 shift registers to read button pushes. Code is scalable to read from a # of shift registers.

* [Thinkercad sketch](https://www.tinkercad.com/things/7BMBGhKhBrG)

![Circuit diagram](ButtonReadChain/SN74HC595-ButtonInputReaderChained.png?raw=true "Sketch")
![Implemented](ButtonReadChain/ButtonReadChain.jpg?raw=true "Implemented")

### [LedFlasher](https://github.com/larsensolutions/arduino/tree/master/LedFlasher) Using a 8 bit 74HC575 to toggle some LED's
Using a 74HC595 shift registers to drive 3 LED's.

* [Thinkercad sketch](https://www.tinkercad.com/things/cHowXQvEdyA)

![Circuit diagram](LedFlasher/ledflasher.png?raw=true "Sketch")

### [WebSocket](https://github.com/larsensolutions/arduino/tree/master/WebSocket) Using Websocket data to control LED status
Using a 74HC595 shift registers to drive LED status using data received from Websocket connection.

### [RaspdusWifi](https://github.com/larsensolutions/arduino/tree/master/RaspdusWifi) ESP8266-07 Wifi chip, will serve as brain in the Raspdus controller project
Basically combines the stuff from the other sketches. In the end this will become a remote control that connects to my wifi at home that talks to my home automation API to control for instance lights.

#### Final results

![Box complete](RaspdusWifi/raspdus-box-complete.jpg?raw=true "Box complete")
![Box knobs](RaspdusWifi/raspdus-box-knobs.jpg?raw=true "Box knobs")
![Box prints](RaspdusWifi/raspdus-box-prints.jpg?raw=true "Box prints")
![Box wiring](RaspdusWifi/raspdus-box-wiring.jpg?raw=true "Box wiring")

<blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">Wifi controller demonstration! 3d printed layout of appartment to show where the lights are with LEDs. The LED states are synced (so I can also use my app). I love the tiny toilet 😁 Parts from <a href="https://twitter.com/kjellcoNorge?ref_src=twsrc%5Etfw">@kjellcoNorge</a> <a href="https://twitter.com/telldus?ref_src=twsrc%5Etfw">@telldus</a> <a href="https://twitter.com/arduino?ref_src=twsrc%5Etfw">@arduino</a> <a href="https://twitter.com/hashtag/esp8266?src=hash&amp;ref_src=twsrc%5Etfw">#esp8266</a> <a href="https://twitter.com/hashtag/Python?src=hash&amp;ref_src=twsrc%5Etfw">#Python</a> <a href="https://twitter.com/hashtag/IoT?src=hash&amp;ref_src=twsrc%5Etfw">#IoT</a> <a href="https://twitter.com/Hacksterio?ref_src=twsrc%5Etfw">@Hacksterio</a> <a href="https://twitter.com/hashtag/3DPrinting?src=hash&amp;ref_src=twsrc%5Etfw">#3DPrinting</a> <a href="https://t.co/gGoQ6ltFRx">pic.twitter.com/gGoQ6ltFRx</a></p>&mdash; Erik Larsen (@grizzlifrog) <a href="https://twitter.com/grizzlifrog/status/1070663566863290368?ref_src=twsrc%5Etfw">December 6, 2018</a></blockquote>
<script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>


#### 3D prints source files
* The box (print coloured parts separately) [Tinkercad 3D print](https://www.tinkercad.com/things/5O3gAvxATRC/edit?sharecode=LnFBwAcFzZKmgHHJWiTbrchXy2RChrDAEr17kh_O0ms=)
* The apartment [Tinkercad 3D print](https://www.tinkercad.com/things/06itOJWX7F3/edit?sharecode=p6LfuG1Tc5tmdaZJKfttCCOc3zg3f6xt6FtNrXc_VN0=)
* Logo and labels [Tinkercad 3D print](https://www.tinkercad.com/things/jhPKKVwyEU6-raspdus-box-logo-and-labels/edit?sharecode=u3jyjOwCSqnDHdXntYfT9-1s8Q0ZC1yVMoiltZoRI98=)

## Resources

* Generate circuit diagrams: [Thinkercad](https://www.tinkercad.com)

## Contact

Erik Andreas Larsen – [@grizzifrog](https://twitter.com/grizzlifrog) – eriklarsen.post@gmail.com