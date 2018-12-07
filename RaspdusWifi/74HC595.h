#include <SPI.h>
/**
 * 74HC595
 * by Erik Andreas Larsen
 * 
 * https://github.com/larsensolutions/arduino
 * https://twitter.com/grizzlifrog
 * 
 **/

// Not able to move this into a class (needs to be static, causing usage problems)
volatile static bool buttonPressed = false;
void pinRead()
{
  buttonPressed = true;
}

// Helpes 
struct RegisterData
{
  int slot;
  int position;
  int value;
};

// Making the code scalable with regards to the number of shift registers we are using in the circuit.
class Register
{
public:
  int data;
  int buttonStates;
  Register()
  {
    data = 0;
    buttonStates = 0;
  }
};

class Controller74HC595
{
private:
  bool searching = false;
  int interruptPin;
  int slaveSelectPin;
  int registerCount;
  Register *registers;

public:
  int activeButtonIndex;
  Controller74HC595(int slaveSelectPin, int registerCount) : Controller74HC595(-1, slaveSelectPin, registerCount)
  {
  }
  Controller74HC595(int interruptPin, int slaveSelectPin, int registerCount)
  {
    this->interruptPin = interruptPin;
    this->slaveSelectPin = slaveSelectPin;
    this->registerCount = registerCount;
  }

  void begin(int state)
  {
    registers = new Register[registerCount];

    Serial.println("Controller74HC595: Initializing");
    // Set our pin modes
    pinMode(slaveSelectPin, OUTPUT);
    if (interruptPin > -1)
    {
      pinMode(interruptPin, INPUT);
      attachInterrupt(digitalPinToInterrupt(interruptPin), pinRead, RISING);
    }
    // Initiate SPI (Serial Peripheral Interface)
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    // Initiate the register
    resetStates(state);
  }

  bool needToHandleButtonPress()
  {
    // As long as we have a button press and we are not already conducting a search,
    // lets find the buttons being pressed!
    if (buttonPressed && !searching)
    {
      searching = true;
      // Allow some delay to enable read of multiple buttons.
      // It is almost human impossible to press two buttons down at the excat time.
      // For now, we only register 1 button press.
      delay(50);
      // We need to check one register at the time
      for (int i = 0; i < registerCount; i++)
      {
        readButtonStates(registers[i]);
      }
      // When we are done, we reset the states and return wether this was a true button press or not
      resetStates(255);
      return isButtonPressed();
    }
    return false;
  }

  bool isButtonPressed()
  {
    for (int i = 0; i < registerCount; i++)
    {
      // Ignore registers with no button pressed
      if (registers[i].buttonStates == 0)
      {
        continue;
      }
      Serial.print("Register ");
      Serial.println(i);
      printBinary(registers[i].buttonStates);
      // Find what button index was pressed
      int t = getHighBitIndex(registers[i].buttonStates);
      Serial.println(t);
      if (t > -1)
      {
        activeButtonIndex = (i * 8) + t;
        return true;
      }
    }
    return false;
  }
  void writeRegisterData(RegisterData data)
  {
    bitWrite(registers[data.slot].data, data.position, data.value);
    writeToRegisters();
  }

  void printData()
  {
    for (int i = 0; i < registerCount; i++)
    {
      printBinary(registers[i].data);
    }
  }

private:
  void resetStates(int to)
  {
    // 1. Important to set all register pins to 1 (ON) before ending the search!
    // Because we will retrigger the RAISE condition on our interruption pin
    // if the button is still pressed. Which is likely due to how fast the loop is.
    setDataToAllRegisters(to); // Equals to 11111111
    writeToRegisters();

    // 2. Updates our states, we are no longer searching, and we know we won't retrigger
    // the interrupt again.
    searching = false;
    buttonPressed = false;

    // If we do want to know how long the button is pressed, or continue trigger when button is pressed,
    // swap step 1 and 2.
  }

  void setDataToAllRegisters(int pattern)
  {
    for (int i = 0; i < registerCount; i++)
    {
      registers[i].data = pattern;
    }
  }

  // Important lesson here: Need to use the & operator to indicate that we want to MODIFY our Register object!
  // If this is forgotten our buttonStates are never set (they only live in the scope of the function)
  void readButtonStates(Register &reg)
  {
    int buttonsOn = 0;
    int check = 1; // Equals to 00000001
    for (int i = 0; i < 8; i++)
    {
      // Reset all registers
      setDataToAllRegisters(0);
      // Load our check byte into the register we are testing
      reg.data = check;
      writeToRegisters();
      if (digitalRead(interruptPin) == HIGH)
      {
        bitWrite(buttonsOn, i, 1);
      }
      // Move our 1 bit to the left, i.e the first next iteration will look like 00000010
      check = check << 1;
    }
    reg.buttonStates = buttonsOn;
  }

  void writeToRegisters()
  {
    // tell the shift-registers we're sending
    digitalWrite(slaveSelectPin, LOW);
    for (int i = registerCount; i > 0; i--)
    {
      SPI.transfer(registers[i - 1].data);
    }
    // tell the shift register we're done and it can now
    // apply the byte pattern to it's output pins.
    digitalWrite(slaveSelectPin, HIGH);
  }

  // Using this to confirm what buttons were pushed
  void printBinary(byte inByte)
  {
    if (Serial)
    {
      Serial.print(inByte);
      Serial.print(" - ");
      for (int b = 7; b >= 0; b--)
      {
        Serial.print(bitRead(inByte, b));
      }
      Serial.println("");
    }
  }

  int getHighBitIndex(byte inByte)
  {
    for (int index = 7; index >= 0; index--)
    {
      int bit = bitRead(inByte, index);
      if (bit == 1)
      {
        return index;
      }
    }
    return -1;
  }
};
