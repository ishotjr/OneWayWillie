#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>


// *courtesy Adafruit SSD1331 library example*

// OLED pins on MKR WiFi 1010
#define sclk 9
#define mosi 8
#define cs   4
#define rst  7
#define dc   6

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// using hardware SPI pins
Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);

enum Distance: byte {
  FAR,
  NEAR,
  NEARER,
  NEAREST
};
const int distanceColors[] = {0x0000,0x001F,0xFFE0,0xF800};

const int piezo = 5;
int proximity = FAR;


void setup() {

  Serial.begin(9600);
  pinMode(piezo, OUTPUT);

  Serial.println("Initializing...");

  display.begin();
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.print("Initializing...");

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


  display.fillScreen(distanceColors[proximity]);
  display.setCursor(2,2);
  display.setTextColor(BLACK);
  display.setTextSize(proximity * 2);
  display.println(proximity);
  
  // buzz when too close, escalating pitch and speed with proximity
  if (proximity > 0) {
    tone(piezo, proximity * 220, 30 * proximity * proximity);
  } else {
    noTone(piezo);
  }

  // for sensor, not tone (which uses own timer)
  delay(250);

}
