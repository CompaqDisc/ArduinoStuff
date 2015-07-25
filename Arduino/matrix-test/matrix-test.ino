#include <LED_Matrix.h>

LED_Matrix Matrix(7, 4);
int rowPins[] = {2, 3, 4, 5};
int colPins[] = {6, 7, 8, 9, 10, 11, 12};
int L1[] = {3, 2};

void setup() {
  Matrix.rows(rowPins);
  Matrix.cols(colPins);
  
  Matrix.on(L1);
}

void loop() {
  
}
