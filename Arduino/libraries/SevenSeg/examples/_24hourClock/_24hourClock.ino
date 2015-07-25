#include <SevenSeg.h>

SevenSeg disp(2, 3, 4, 5, 6, 7, 8); // initialize display with correct pins
const int numOfDigits = 4; // digits on display
int digitPins[numOfDigits] = {10, 11, 12, 13}; // cathodes / anodes for selecting digit
int hour = 12; // default time (hour)
int minute = 00; // default time (minute)
char seperator = '.'; // separator between hour and minute
int seconds = 0; // stores seconds
long previousMillis = 0; // comparison for seconds elapsed
long second_def = 1000; // 1000ms = 1sec

void setup() {
  disp.setDigitPins(numOfDigits, digitPins); // sets up display
  disp.setCommonCathode(); // sets digitPins as cathodes
  disp.setDPPin(9); // sets decimal point (or colon if applicable) pin
  pinMode(A0, INPUT); // minute up button input pin
  pinMode(A1, INPUT); // same as above for hour
}

void loop() {
  unsigned long currentMillis = millis();
  disp.writeClock(hour, minute, seperator);
  if (digitalRead(A1) == HIGH) {
    hour++;
    delay(250);
  }
  if (hour > 23) {
    hour = 0;
  }
  if (digitalRead(A0) == HIGH) {
    minute++;
    delay(250);
  }
  if (minute > 59) {
    minute = 0;
    hour++;
  }
  if (currentMillis - previousMillis > second_def) {
    previousMillis = currentMillis;
    seconds++;
  }
  if (seconds > 59) {
    seconds = 0;
    minute++;
  }
}
