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
#include <Keypad.h>

#define SUBMIT -1
#define NOTHING -2
#define CANCEL -3

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 31, en = 30, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {45, 49, 51, 39}; 
byte colPins[COLS] = {47, 43, 41};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


int number_to_display = 0, input = 0, num = 0, reset_pin = 27;
int counter[4] = {0,0,0,0};

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);

  // pins for sending data to FPGA
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  
  // set reset pin to low
  digitalWrite(reset_pin, LOW);
}


void loop() {
   lcd.clear();
   
   // get input from keypad
   input = get_input();

   // if valid input
   if (input > 0) {
      counter[0] = 0;
      counter[1] = 0;
      counter[2] = 0;
      counter[3] = 0;
      seed(input);
   }
   else {
      // get number from FPGA
      number_to_display = get_number();
      
      // display counter stats
      lcd.setCursor(0, 0);
      lcd.print(counter[0]);
      lcd.print('!');
      lcd.print(counter[1]);
      lcd.print('!');
      lcd.print(counter[2]);
      lcd.print('!');
      lcd.print(counter[3]);
      
      // display generated random number
      lcd.setCursor(0, 1);
      lcd.print(number_to_display);
      
      delay(1000);
   }
}

// gets input from FPGA
int get_number() {
  int sig = digitalRead(34) + 2*digitalRead(35);
  counter[sig]++;
  
  return (1*digitalRead(6) +
          2*digitalRead(7) + 
          4*digitalRead(8) + 
          8*digitalRead(9) +
          16*digitalRead(10) +
          32*digitalRead(11) +
          64*digitalRead(12) +
          128*digitalRead(13) +
          256*digitalRead(24) +
          512*digitalRead(25));
}


// gets input from Keypad
int get_num() {
  char customKey = customKeypad.getKey();
  
  switch (customKey) {
      case '0':
          return 0;
      case '1':
          return 1;
      case '2':
          return 2;
      case '3':
          return 3;
      case '4':
          return 4;
      case '5':
          return 5;
      case '6':
          return 6;
      case '7':
          return 7;
      case '8':
          return 8;
      case '9':
          return 9;
      case '*':
          return CANCEL;
      case '#':
          return SUBMIT;
  }

  return NOTHING;
}


int get_input() {
    num = get_num();
    if (num <= 0) {
        return NOTHING;
    }
    
    delay(100);
    input = 0;
    lcd.setCursor(0, 0);
    lcd.print("INPUT:");
    while (num == NOTHING || num >= 0) {
        if (num != NOTHING) {            
            // max seed is 255
            if (10*input + num <= 255) {
               input = 10*input + num;
               lcd.print(num);
            }
        }
        
        num = get_num();
        delay(100);
    }

    if (num == SUBMIT) {
        return input;
    }

    return CANCEL;
}

// send seed value to FPGA
void seed(int val) {
    digitalWrite(14, val%2);
    val = (val) >> 1;
    digitalWrite(15, val%2);
    val = (val) >> 1;
    digitalWrite(16, val%2);
    val = (val) >> 1;
    digitalWrite(17, val%2);
    val = (val) >> 1;
    digitalWrite(18, val%2);
    val = (val) >> 1;
    digitalWrite(19, val%2);
    val = (val) >> 1;
    digitalWrite(20, val%2);
    val = (val) >> 1;
    digitalWrite(21, val%2);

    digitalWrite(reset_pin, 1);
    delay(1000);
    digitalWrite(reset_pin, 0);
}
