#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const int rows = 4;
const int cols = 4;

char pressed = 'N';
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const int rowPins[] = {11, 10, 9, 8};
const int colPins[] = {7, 6, 5, 4};

LiquidCrystal_I2C lcd(0x20, 16, 2);
Keypad keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.blink();
  lcd.setCursor(0, 0);

  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print("Testing LCD");
}

void loop() {
  pressed = keypad.getKey();

  if (pressed != NO_KEY) {
    digitalWrite(LED_BUILTIN, HIGH);
    lcd.print(pressed);
    lcd.scrollDisplayLeft();
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    lcd.noBlink();
  }
}
