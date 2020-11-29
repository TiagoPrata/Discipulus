long UltraSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);  
  long Duration = pulseIn(echoPin,HIGH);
  return Duration;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void readUltraSensors() {
  longSensorValue[0] = UltraSensor(Sensor1Trig, Sensor1Echo);
  longSensorValue[1] = UltraSensor(Sensor2Trig, Sensor2Echo);
  longSensorValue[2] = UltraSensor(Sensor3Trig, Sensor3Echo);
  longSensorValue[3] = UltraSensor(Sensor4Trig, Sensor4Echo);
  longSensorValue[4] = UltraSensor(Sensor5Trig, Sensor5Echo);
  longSensorValue[5] = UltraSensor(Sensor6Trig, Sensor6Echo);
  longSensorValue[6] = UltraSensor(Sensor7Trig, Sensor7Echo);
  longSensorValue[7] = UltraSensor(Sensor8Trig, Sensor8Echo);
  
  for (int i = 0; i < 8; i++) {
    sensorValue[i] = longSensorValue[i] / 100000.0;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorValue[i], 5);
  }
}
