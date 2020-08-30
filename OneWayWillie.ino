enum Distance: byte {
  FAR,
  NEAR,
  NEARER,
  NEAREST
};

const int piezo = 5;
int proximity = FAR;

void setup() {
 
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);

}

void loop() {

  // Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V
  int sensorValue = analogRead(A0);
  Serial.print("sensorValue: ");
  Serial.println(sensorValue);

  if (sensorValue > 800) {
    proximity = NEAREST;
  } else if (sensorValue > 400) {
    proximity = NEARER;
  } else if (sensorValue > 220) {
    proximity = NEAR;
  } else {
    proximity = FAR;
  }
  Serial.print("proximity: ");
  Serial.println(proximity);

  // buzz when too close, escalating pitch and speed with proximity
  if (proximity > 0) {
    tone(piezo, proximity * 220, 30 * proximity * proximity);
  } else {
    noTone(piezo);
  }

  // for sensor, not tone (which uses own timer)
  delay(250);

}
