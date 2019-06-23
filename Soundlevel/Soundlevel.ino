#define SoundSensorPin A0  //this pin read the analog voltage from the sound level meter
#define VREF  5.0  //voltage on AREF pin,default:operating voltage

void setup() {
  Serial.begin(115200);  //initial the Serial
}

void loop() {
  //if (Serial.available())  {
    float voltageValue,dbValue;
    voltageValue = analogRead(SoundSensorPin) / 1024.0 * VREF;
    dbValue = voltageValue * 50.0;  //convert voltage to decibel value
    Serial.print(dbValue,1);
    Serial.println(" dBA");
    delay(125);
  //}
}
