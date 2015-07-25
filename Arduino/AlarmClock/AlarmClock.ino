#include <SevenSeg.h>

SevenSeg disp(2, 3, 4, 5, 6, 7, 8);
const int numOfDigits = 4;
int digitPins[numOfDigits] = {10, 11, 12, 13};
int hour = 12;
int minute = 00;
int seconds = 0;
long secPrevMillis = 0;
long blinkPrevMillis = 0;
long second_def = 1000;
long blink_freq = 500;
boolean pm = false;
boolean reset = false;
boolean blinkOn = false;
char seperator = '_';

void setup() {
  disp.setDigitPins(numOfDigits, digitPins);
  disp.setCommonCathode();
  disp.setDPPin(9);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  unsigned long secCurMillis = millis();
  unsigned long blinkCurMillis = millis();
  disp.writeClock(hour, minute, seperator);
  if (digitalRead(A1) == HIGH) {
    hour++;
    delay(250);
  }
  if (hour > 12) {
    hour = 01;
    reset = true;
  }
  if (hour > 11 && reset == true) {
    togglePM();
    reset = false;
  }
  if (digitalRead(A0) == HIGH) {
    minute++;
    delay(250);
  }
  if (minute > 59) {
    minute = 00;
    hour++;
  }
  if (secCurMillis - secPrevMillis > second_def) {
    secPrevMillis = secCurMillis;
    seconds++;
  }
  if (blinkCurMillis - blinkPrevMillis > blink_freq) {
    blinkPrevMillis = blinkCurMillis;
    blinkSep();
  }
  if (seconds > 59) {
    seconds = 0;
    minute++;
  }
  if (pm == true) {
    disp.write("    .");
  }
}

void togglePM() {
  if (pm == false)
    pm = true;
  else
    pm = false;
}

void blinkSep() {
  if (blinkOn == false) {
    blinkOn = true;
    seperator = '.';
  }
  else {
    blinkOn = false;
    seperator = '_';
  }
}
