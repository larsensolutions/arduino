/*
References:

http://techvalleyprojects.blogspot.com/2012/06/arduino-control-escmotor-arduino-code.html
https://www.arduino.cc/en/Tutorial/Sweep
https://forum.arduino.cc/index.php?topic=270309.0
*/
#include <Servo.h>

Servo camera, ESCleft;

#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs

String data = "";

void setup()
{
    ESCleft.attach(9, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    ESCleft.write(MIN_PULSE_LENGTH);
    Serial.begin(9600);
    Serial.println("Turn on ESC - Should start in 'use mode', already calibrated.");
    // Assess if shold use relay to control ESC power.
}

void loop()
{
    if (Serial.available() > 0)
    {
        char ch = Serial.read();
        if (ch != 10) // 10 is 'newline'
        {
            data += ch;
        }
        else
        {
            data.trim();
            Serial.print("Data: ");
            Serial.println(data);
            if (data == "c")
            {
                Serial.println("Should enter calibration mode!");
            }
            else
            {
                int val = data.toInt();
                Serial.println(val);
                if (val > -1 && val < 180)
                {
                    moveCamera(val);
                }
                else
                {
                    ESCleft.write(val);
                }
            }
            data = "";
        }
    }
}

/* 
This will keep servo from doing unwanted movement when turning Arduino on/off.
*/
void moveCamera(int angle)
{
    camera.attach(10);
    camera.write(angle);
    delay(1000); // Let the servo work before detach
    camera.detach();
}