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
#define BLACK           0x0000
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
const int distanceColors[] = {0xFFE0,0xFFE0,0xF81F,0xF800};

const int piezo = 5;
int proximity = FAR;


void setup() {

  Serial.begin(9600);
  pinMode(piezo, OUTPUT);

  Serial.println("Initializing...");

  display.begin();
  display.fillScreen(WHITE);

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

  drawFace(proximity);
  
  // buzz when too close, escalating pitch and speed with proximity
  if (proximity > 0) {
    tone(piezo, proximity * 220, 30 * proximity * proximity);
  } else {
    noTone(piezo);
  }

  // for sensor, not tone (which uses own timer)
  delay(250);

}

void drawFace(byte distance) {
  
  const uint16_t eyeRadius = 4;
  const uint16_t mouthRadius = 6;
  
  // head
  display.fillCircle(display.width() / 2, display.height() / 2, display.height() / 2, distanceColors[distance]);

  // eyes
  display.fillCircle(display.width() / 3, 2 * display.height() / 5, eyeRadius, BLACK);
  display.fillCircle(2 * display.width() / 3, 2 * display.height() / 5, eyeRadius, BLACK);

  if (distance == NEAREST) {
    // mask eyes to look angry
    display.fillTriangle(display.width() / 3, 2 * display.height() / 5 - eyeRadius, 
    2 * display.width() / 3, 2 * display.height() / 5 - eyeRadius, 
    display.width() / 2, display.height() / 2, distanceColors[distance]);
  }
  
  // mouth
  display.fillCircle(display.width() / 2, 4 * display.height() / 5, mouthRadius, BLACK);

  if ((distance == NEAREST) || (distance == NEARER)) {
    // mask mouth circle to look worried
    display.fillRect(display.width() / 2 - mouthRadius, 4 * display.height() / 5, 
      mouthRadius * 2 + 1, mouthRadius + 1, distanceColors[distance]);
  } else if (distance == FAR) {
    // mask mouth circle to create smile
    display.fillRect(display.width() / 2 - mouthRadius, 4 * display.height() / 5 - mouthRadius, 
      mouthRadius * 2 + 1, mouthRadius, distanceColors[distance]);
  }
  
}
