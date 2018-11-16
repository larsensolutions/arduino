#include <SPI.h>
/*
  Basic idea on how to read if a button is pushed: 
  Ref: https://wbsimms.com/use-74hc595-monitor-many-digital-inputs/
  
  On startup:
  Set all 74HC595 output pins high
  The un-pressed buttons prevent current from flowing to the interrupt pin
  Once a button, current flows to the interrupt pin firing the interrupt event
  In side the interrupt event, you’ll do the following:
    Turn all 74HC595 pins low
    Loop through each 74HC595 output pin turning it high, and checking the status of the interrupt pin.
      If the pin is low, that button isn’t pressed.
      If the pin is high, that button IS pressed.

  Looping through each output pin in the 74HC595 is very fast as long as you’re not doing too much in the loop.
*/

// PINS

const int interruptPin = 2;
const int slaveSelectPin = 10;

// STATES

// Variables shared between main loop and interrupt event should be marked volatile
volatile bool buttonPressed = false;
bool searching = false;
byte buttonsOn = 0;

void setup() {
  // Start serial and print script version
  Serial.begin(115200);
  Serial.println("Button Read: Version 1");

  // Set our pin modes
  pinMode(interruptPin, INPUT);
  pinMode(slaveSelectPin, OUTPUT);

  // Initiate SPI (Serial Peripheral Interface)
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  // Initiate the register
  writeToRegister(255); // Set all outputs to 1
  Serial.println("Setting all output pins ON!");

  // Attach our events
  attachInterrupt(digitalPinToInterrupt(interruptPin), pinRead, RISING);
}

void loop() {
  if (buttonPressed && !searching) {
    // Allow some delay to enable read of multiple buttons.
    // It is almost human impossible to press two buttons down at the excat time.
    delay(50);
    findButtonPressed();
    if(buttonsOn != 0){
       // 0 indicates a false read, so discard printing it.
       // False read will happen sometimes on button release, making
       // the interrupt pin go HIGH and trigger a new search. However,
       // since no buttons is actually pressed by the time the search runs we get no hits
       Serial.println(buttonsOn);
    }
  }
}

void pinRead() {
  buttonPressed = true;
}

void findButtonPressed() {
  searching = true;
  buttonsOn = 0;
  
  byte check = 1; // Equals to 00000001
  for (int i = 0; i < 8; i++) {
    // Load our check byte into the register
    writeToRegister(check);
    if (digitalRead(interruptPin) == HIGH) {
      bitWrite(buttonsOn, i, 1);
    } 
    // Move our 1 bit to the left, i.e the first next iteration will look like 00000010
    check = check << 1; 
  }
  writeToRegister(255); // Equals to 11111111, sets all outputs to 1 basically
 
  // Updates our states, we are no longer searching
  searching = false;
  buttonPressed = false;
}

void writeToRegister(int data) {
  // tell the shift-registers we're sending
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(data); // Transfer data to the SN74HC595
  // tell the shift register we're done and it can now 
  // apply the byte pattern to it's output pins.
  digitalWrite(slaveSelectPin, HIGH);
}
