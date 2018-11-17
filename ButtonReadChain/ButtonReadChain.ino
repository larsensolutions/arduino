#include <SPI.h>
/**
 * ButtonReadChain.ino
 * by Erik Andreas Larsen
 * 
 * https://github.com/larsensolutions/arduino
 * https://twitter.com/grizzlifrog
 * 
 **/

/**
 * The yey or trick this time to get a less noise circuit is to add a conductor between the latch pins of the chained registers!!
 * Without this one, there was flicker between the output pins on the second register.
 * REFs: 
 * https://www.arduino.cc/en/Tutorial/ShiftOut
 * https://arduino.stackexchange.com/questions/6512/going-from-one-shift-register-to-two-shift-registers
 * 
 * "From now on those will be refered to as the dataPin, the clockPin and the latchPin respectively. 
 * Notice the 0.1"f capacitor on the latchPin, if you have some flicker 
 * when the latch pin pulses you can use a capacitor to even it out."
 * 
 * Resistors "slow" the flow of current. Capacitors "slow" the changes in the flow. 
 * Of course "slow" is not correct but in the context of the common water metaphor, it works.
 * /

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

// Helper class to make the code scalable with regards to the number of shift registers we are using in the circuit.
class Register {
    public:
    int data;
    int buttonStates;
    Register(){
      data = 0;
      buttonStates = 0;
    }
};

// Specify how many registers we have in our curcuit
// Have only tested up to two registers so far
const int registerCount = 2;
Register* registers = new Register[registerCount];

void setup() {
  // Start serial and print script version
  Serial.begin(115200);
  Serial.println("Button Read Chain: Version 5");

  // Set our pin modes
  pinMode(interruptPin, INPUT);
  pinMode(slaveSelectPin, OUTPUT);

  // Initiate SPI (Serial Peripheral Interface)
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  // Initiate the register
  resetStates();
  // Attach our events
  attachInterrupt(digitalPinToInterrupt(interruptPin), pinRead, RISING);
}

// Here our logic begins!

void loop() {
  // As long as we have a button press and we are not already conducting a search,
  // lets find the buttons being pressed!
  if (buttonPressed && !searching) {
    // Allow some delay to enable read of multiple buttons.
    // It is almost human impossible to press two buttons down at the excat time.
    delay(50);
    // We need to check one register at the time
    for(int i = 0; i < registerCount;i++){
       readButtonStates(registers[i]);
    }
    // When we are done, lets print the results and get ready for more button pushes
    printButtonStates();
    resetStates();
  }
}

void resetStates(){
  // 1. Important to set all register pins to 1 (ON) before ending the search!
  // Because we will retrigger the RAISE condition on our interruption pin 
  // if the button is still pressed. Which is likely due to how fast the loop is.
  setDataToAllRegisters(255); // Equals to 11111111
  writeToRegisters();

  // 2. Updates our states, we are no longer searching, and we know we won't retrigger
  // the interrupt again.
  searching = false;
  buttonPressed = false;

  // If we do want to know how long the button is pressed, or continue trigger when button is pressed,
  // swap step 1 and 2.
}

void setDataToAllRegisters(int pattern){
   for(int i = 0; i < registerCount;i++){
     registers[i].data=pattern;
  }
}

void printButtonStates(){
   for(int i = 0; i < registerCount;i++){
     if(registers[i].buttonStates==0){
       continue;
     }
     Serial.print("Register ");
     Serial.println(i);
     printBinary(registers[i].buttonStates);
  }
}

void pinRead() {
  buttonPressed = true;
}

// Important lesson here: Need to use the & operator to indicate that we want to MODIFY our Register object!
// If this is forgotten our buttonStates are never set (they only live in the scope of the function)
void readButtonStates(Register& reg) {
  searching = true;
  int buttonsOn = 0;
  int check = 1; // Equals to 00000001
  for (int i = 0; i < 8; i++) {
    // Reset all registers
    setDataToAllRegisters(0);
    // Load our check byte into the register we are testing
    reg.data=check;
    writeToRegisters();
    if (digitalRead(interruptPin) == HIGH) {
      bitWrite(buttonsOn, i, 1);
    }
    // Move our 1 bit to the left, i.e the first next iteration will look like 00000010
    check = check << 1; 
  }
   reg.buttonStates = buttonsOn;
}

void writeToRegisters() {
    // tell the shift-registers we're sending
  digitalWrite(slaveSelectPin, LOW);
  for(int i = registerCount; i > 0; i--){
     SPI.transfer(registers[i-1].data);
  }
  // tell the shift register we're done and it can now 
  // apply the byte pattern to it's output pins.
  digitalWrite(slaveSelectPin, HIGH);
}

// Using this to confirm what buttons were pushed
void printBinary(byte inByte)
{
  Serial.print(inByte);
  Serial.print(" - ");
  for (int b = 7; b >= 0; b--)
  {
    Serial.print(bitRead(inByte, b));
  }
   Serial.println("");
}