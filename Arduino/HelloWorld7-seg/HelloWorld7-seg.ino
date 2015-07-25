#include <SevenSeg.h>

SevenSeg disp(2, 3, 4, 5, 6, 7, 8);
const int numOfDigits = 4;
int digitPins[numOfDigits] = {10, 11, 12, 13};

void setup() {
  
  disp.setDigitPins(numOfDigits, digitPins);
  disp.setCommonCathode();
  disp.setDPPin(9);
  
}

void loop() {
  disp.write("Hell");
  disp.write("ello");
  disp.write("llo ");
  disp.write("lo W");
  disp.write("o Wo");
  disp.write(" Wor");
  disp.write("Worl");
  delay(10000);
}
