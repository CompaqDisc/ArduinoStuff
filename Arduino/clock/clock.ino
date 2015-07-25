#include <SevenSeg.h>

SevenSeg disp(2, 3, 4, 5, 6, 7, 8);
const int numOfDigits = 4;
int digitPins[numOfDigits] = {10, 11, 12, 13};
int hour = 12;
int minute = 00;
char seperator = '.';
int seconds = 0;
long previousMillis = 0;
long second_def = 1000;

void setup() {
  disp.setDigitPins(numOfDigits, digitPins);
  disp.setCommonCathode();
  disp.setDPPin(9);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
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
