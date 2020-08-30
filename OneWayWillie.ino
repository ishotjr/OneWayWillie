const int piezo = 5;

void setup(){
 
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);

}

void loop(){

  // Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  // buzz when too close, escalating pitch with proximity
  if (sensorValue > 210) {
    tone(piezo, sensorValue);
  } else {
    noTone(piezo);
  }

  // for sensor, not tone (which uses own 
  delay(100);

}
