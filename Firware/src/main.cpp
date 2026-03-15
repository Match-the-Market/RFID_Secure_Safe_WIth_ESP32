#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED
const int sda = 21;
const int scl = 22;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// LED
const int greenled = 27;

void setup() {
  Serial.begin(115200);

  // LED setup
  pinMode(greenled, OUTPUT);
  digitalWrite(greenled, LOW);

  // OLED setup
  Wire.begin(sda, scl);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  // Show welcome message
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(15, 10);
  oled.println("Welcome!");
  oled.setTextSize(1);
  oled.setCursor(20, 40);
  oled.println("Initializing...");
  oled.display();

  delay(2000);

  // Flash green LED 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(greenled, HIGH);
    delay(1000);
    digitalWrite(greenled, LOW);
    delay(1000);
  }

  // Update OLED after flashing
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(25, 25);
  oled.println("Ready!");
  oled.display();
}

void loop() {
  // Nothing here
}