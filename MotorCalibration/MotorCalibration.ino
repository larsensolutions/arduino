/**
 * Usage, according to documentation(https://www.firediy.fr/files/drone/HW-01-V4.pdf) :
 *     1. Plug your Arduino to your computer with USB cable
 *     2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK
 *     3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed
 *     4. Type 0 to send min throttle
 *     5. Several "beep" tones emits, which means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo)
 *     6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed
 *     7. Type 2 to launch test function. This will send min to max throttle to ESCs to test them
 *
 * original @author lobodol <grobodol@gmail.com>
 * Modified by Erik <eriklarsen.post@gmail.com>
 */

#include <Servo.h>

#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs

Servo toCalibrate;
char data;

void setup()
{
    Serial.begin(9600);

    toCalibrate.attach(9, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    toCalibrate.write(MAX_PULSE_LENGTH); // To calibrate throttle set motor pin to high
    displayInstructions();
}

void loop()
{
    if (Serial.available())
    {
        data = Serial.read();

        switch (data)
        {
        case 48: // 0
            Serial.println("Sending minimum throttle");
            toCalibrate.writeMicroseconds(MIN_PULSE_LENGTH);
            break;
        case 49: // 1
            Serial.println("Sending maximum throttle");
            toCalibrate.writeMicroseconds(MAX_PULSE_LENGTH);
            break;
        case 50: // 2
            runMinToMaxThrottle();
            break;
        }
    }
}

void runMinToMaxThrottle()
{
    Serial.println("Running test in");
    for (int i = 3; i > 0; i--)
    {
        Serial.println(i);
        delay(1000);
    }
    for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5)
    {
        Serial.print("Pulse length = ");
        Serial.println(i);
        toCalibrate.writeMicroseconds(i);
        delay(200);
    }
    Serial.println("Stopping");
    toCalibrate.writeMicroseconds(MIN_PULSE_LENGTH);
}

void displayInstructions()
{
    Serial.println("Turn on the ESC power");
    Serial.println("(3 beeps) - You should hear the ESC startup tones.");
    Serial.println("(2 beeps) - Shortly afterwards, you should hear two beeps indicating that the ESC has registered the high throttle value");
    Serial.println("\t0 : Send min throttle within 5 seconds, otherwise the ESC enters program mode");
    Serial.println("You should hear several beeps indicating the input voltage supplied to the ESC followed by a long beep indicating that the low throttle has been set. ESC is now ready to be used");
    Serial.println("\t2 : Run test function\n");
}