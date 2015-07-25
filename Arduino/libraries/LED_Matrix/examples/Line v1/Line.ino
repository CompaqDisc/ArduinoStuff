#include <LED_Matrix.h>

LED_Matrix matrix;
int wait = 1;

void setup() {
	matrix.rows(17, 16, 12, 7, 11, 5, 4, 14);
	matrix.cols(6, 3, 8, 2, 13, 9, 15, 10);
}

void loop() {
	matrix.on(1, 1);
	delay(wait);
	matrix.off(1, 1);
	
	matrix.on(2, 1);
	delay(wait);
	matrix.off(2, 1);
	
	matrix.on(3, 1);
	delay(wait);
	matrix.off(3, 1);
	
	matrix.on(4, 1);
	delay(wait);
	matrix.off(4, 1);
	
	matrix.on(5, 1);
	delay(wait);
	matrix.off(5, 1);
	
	matrix.on(6, 1);
	delay(wait);
	matrix.off(6, 1);
	
	matrix.on(7, 1);
	delay(wait);
	matrix.off(7, 1);
	
	matrix.on(8, 1);
	delay(wait);
	matrix.off(8, 1);
}
