/*
 The circuit connections:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD DB4 pin to digital pin 5
 * LCD DB5 pin to digital pin 4
 * LCD DB6 pin to digital pin 3
 * LCD DB7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 1, en = 0, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int number_to_display;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
   number_to_display = get_number();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(number_to_display);
   delay(100);
}

int get_number() {
  return (1*digitalRead(6) + 2*digitalRead(7) + 4*digitalRead(8) + 8*digitalRead(9) + 16*digitalRead(10) + 32*digitalRead(11) + 64*digitalRead(12) + 128*digitalRead(13));
}
