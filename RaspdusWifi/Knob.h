// Potentiomater logic for dimming lights

// const int totalSamples = 20;
// double samples = totalSamples;

// double total = 0;
// double currentVal = 0;
// double siblingVal = 0;
// int average = 0;

// currentVal = analogRead(A0);
// currentVal = map(currentVal, 0, 1023, 0, 255);

// if (siblingVal == currentVal)
// {
//     return;
// }
// siblingVal = currentVal;
// samples--;
// Serial.println(currentVal);
// delay(20);

// total += currentVal;

// if (samples == 0)
// {
//     samples = totalSamples;
//     average = total / samples;
//     total = 0;
// }

// if (abs(prevVal - average) > 15)
// {
//     sendRequest(average);
//     prevVal = average;
// }