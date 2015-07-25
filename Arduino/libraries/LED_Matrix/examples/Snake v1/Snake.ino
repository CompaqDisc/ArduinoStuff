#include <LED_Matrix.h>

LED_Matrix matrix;
int wait = 50;

void setup() {
	matrix.rows(17, 16, 12, 7, 11, 5, 4, 14);
	matrix.cols(6, 3, 8, 2, 13, 9, 15, 10);
}

void loop() {
	matrix.on(1, 1);
	delay(wait);
        matrix.off(1, 5);

	matrix.on(2, 1);
	delay(wait);
	matrix.off(1, 4);

	matrix.on(3, 1);
	delay(wait);
	matrix.off(1, 3);

	matrix.on(4, 1);
	delay(wait);
	matrix.off(1, 2);

	matrix.on(5, 1);
	delay(wait);
	matrix.off(1, 1);

	matrix.on(6, 1);
	delay(wait);
	matrix.off(2, 1);
	
	matrix.on(7, 1);
	delay(wait);
	matrix.off(3, 1);
	
	matrix.on(8, 1);
	delay(wait);
	matrix.off(4, 1);

        matrix.on(8, 2);
	delay(wait);
	matrix.off(5, 1);

        matrix.on(8, 3);
	delay(wait);
	matrix.off(6, 1);

        matrix.on(8, 4);
	delay(wait);
	matrix.off(7, 1);

        matrix.on(8, 5);
	delay(wait);
	matrix.off(8, 1);

        matrix.on(8, 6);
	delay(wait);
	matrix.off(8, 2);

        matrix.on(8, 7);
	delay(wait);
	matrix.off(8, 3);

        matrix.on(8, 8);
	delay(wait);
	matrix.off(8, 4);

        matrix.on(7, 8);
	delay(wait);
	matrix.off(8, 5);

        matrix.on(6, 8);
	delay(wait);
	matrix.off(8, 6);

        matrix.on(5, 8);
	delay(wait);
	matrix.off(8, 7);

        matrix.on(4, 8);
	delay(wait);
	matrix.off(8, 8);

        matrix.on(3, 8);
	delay(wait);
	matrix.off(7, 8);

        matrix.on(2, 8);
	delay(wait);
	matrix.off(6, 8);

        matrix.on(1, 8);
	delay(wait);
	matrix.off(5, 8);

        matrix.on(1, 7);
	delay(wait);
	matrix.off(4, 8);

        matrix.on(1, 6);
	delay(wait);
	matrix.off(3, 8);

        matrix.on(1, 5);
	delay(wait);
	matrix.off(2, 8);

        matrix.on(1, 4);
	delay(wait);
	matrix.off(1, 8);

        matrix.on(1, 3);
	delay(wait);
	matrix.off(1, 7);

        matrix.on(1, 2);
	delay(wait);
	matrix.off(1, 6);
}
