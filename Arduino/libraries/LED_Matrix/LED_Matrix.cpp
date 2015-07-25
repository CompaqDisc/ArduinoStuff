#include "Arduino.h"
#include "LED_Matrix.h"

	LED_Matrix::LED_Matrix(int width, int height)
	{
		_width = width;
		_height = height;
	}

	void LED_Matrix::rows(int rows[])
	{
		_rows[] = rows[];
		int i = 0;
		for(i < _height + 1) {
			pinMode(_rows[i], INPUT);
			i++
		}
	}

	void LED_Matrix::cols(int cols[])
	{
		_cols[] = cols[];
		int i = 0;
		for(i < _width + 1) {
			pinMode(_cols[i], OUTPUT);
			i++
		}
	}

	void LED_Matrix::on(int xy[])
	{
		_xy[] = xy[];
		_x = _xy[0];
		_y = _xy[1];
		digitalWrite(cols[_x], HIGH);
		pinMode(rows[_y], OUTPUT);
	}

	void LED_Matrix::off(int xy[])
	{
		_xy[] = xy[];
		_x = _xy[0];
		_y = _xy[1];
		digitalWrite(cols[_x], LOW);
		pinMode(rows[_y], INPUT);
	}