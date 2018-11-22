/**
 * LedFlasher.ino
 * by Erik Andreas Larsen
 * 
 * https://github.com/larsensolutions/arduino
 * https://twitter.com/grizzlifrog
 * 
 **/

#include <SPI.h>
const int SSpin = 16; //10 on the Arduino, 4 on the ESP;

void setup() {
  Serial.begin(115200); 
  pinMode(SSpin, OUTPUT);
  digitalWrite(SSpin, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
}

void loop() {
  Serial.println("LED Flasher: Version 1");
  write(0); // 00000000
  write(1); // 00000001
  write(2); // 00000010
  write(4); // 00000100
  write(7); // 00000111
}

void write(int data){
   digitalWrite(SSpin, LOW); //Disable any internal transference in the SN74HC595
   SPI.transfer(data); //Transfer data to the SN74HC595
   digitalWrite(SSpin, HIGH); //Start the internal data transference in the SN74HC595
   delay(1000); //Wait for next iteration
}
