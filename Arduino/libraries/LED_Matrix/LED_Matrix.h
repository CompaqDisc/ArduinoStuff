/*
	LED_Matrix.h - Library for LED Matrices.
	Created by Herobrine2Nether, May 21, 2015.
	Released into the public domain.
*/
#ifndef LED_Matrix_h
#define LED_Matrix_h

#include "Arduino.h"

class LED_Matrix
{
	public:
		LED_Matrix(int width, int height);
		void rows(int rows[]);
		void cols(int cols[]);
		void on(int xy[]);
		void off(int xy[]);
		//void frame();
	private:
		int _width;
		int _height;
		int _rows[];
		int _cols[];
		int _xy[];
		int _x;
		int _y;
};

#endif