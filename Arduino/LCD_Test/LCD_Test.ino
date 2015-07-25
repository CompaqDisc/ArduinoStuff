// include the library code:
#include <LiquidCrystal.h>

char msg[] = {72, 101, 114};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
}

void loop() {
  
  int i = 0;
  
  for (i < 4; i++;) {
    lcd.print(msg[i]);
    delay(500);
  }
  //lcd.autoscoll();
}

