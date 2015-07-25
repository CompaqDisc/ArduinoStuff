#include <SevenSeg.h>

SevenSeg disp(2, 3, 4, 5, 6, 7, 8);
const int numOfDigits = 4;
int digitPins[numOfDigits] = {10, 11, 12, 13};
int num = 0;
int offSet = 0;

void setup() {
  
  disp.setDigitPins(numOfDigits, digitPins);
  disp.setCommonCathode();
  disp.setDPPin(9);
  
}

void loop() {
  disp.write(millis() / 1000);
}
