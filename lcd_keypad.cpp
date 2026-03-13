#include <LiquidCrystal_I2C.h>
#include <Arduino.h

// C++ code
//
#include<Wire.h>
#include <Keypad.h> // library for keypad
const int rows = 4;
const int cols =4;
char pressed = 'N';
char keys [rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const int rowPins[] = {11,10,9,8};
const int colPins[]= {7,6,5,4};

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x20,16,2);
Keypad kypad = Keypad(makeKeymap(keys), rowPins, colPins, rows,cols);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.blink();
  lcd.setCursor(0,0);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print("Testing LCD");
}

void loop()
{
  pressed = kypad.getKey();
  if (pressed != NO_KEY) {
    digitalWrite(LED_BUILTIN, HIGH);
    lcd.print(pressed);
    lcd.scrollDisplayLeft();

  } else {
    digitalWrite(LED_BUILTIN, LOW);
    lcd.noBlink();
  }

}