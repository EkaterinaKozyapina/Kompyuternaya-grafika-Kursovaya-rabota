#pragma once
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
#include <math.h>
#include"parametrs.h"

void initialization();

void moving(int x, int y, int z); //перемещение
void scaling(float s); //масштабирование
void turn(float x, float y, float z); //поворот

void mull(); //функция унажает массивы x, y, z на матрицу преобразования (умножает 4 точки. потом вызывает функцию fit)
void zero_matrix(); //функция обнуляет матрицу преобразования
void centre(int & x_centre, int & y_centre, int & z_centre); //функция подсчитывет центральную точку фигуры

void initialization()
{
	// Прямоугольная призма
	x[0] = 400; y[0] = 300; z[0] = 110;
	x[1] = 400; y[1] = 200; z[1] = 110;
	x[2] = 470; y[2] = 200; z[2] = 110;
	x[3] = 470; y[3] = 300; z[3] = 110;

	x[4] = 410; y[4] = 280; z[4] = 10;
	x[5] = 410; y[5] = 180; z[5] = 10;
	x[6] = 480; y[6] = 180; z[6] = 10;
	x[7] = 480; y[7] = 280; z[7] = 10;

	// Треугольная призма
	x[8] = 460; y[8] = 290; z[8] = 60;
	x[9] = 490; y[9] = 190; z[9] = 60;
	x[10] = 520; y[10] = 200; z[10] = 110;
	x[11] = 490; y[11] = 300; z[11] = 110;
	x[12] = 540; y[12] = 180; z[12] = 10;
	x[13] = 510; y[13] = 280; z[13] = 10;

	zero_matrix();

	xLight = 500;
	yLight = 1;
	zLight = 60;

	xPl[0] = 470; yPl[0] = 500; zPl[0] = 20;
	xPl[1] = 570; yPl[1] = 500; zPl[1] = 20;
	xPl[2] = 490; yPl[2] = 520; zPl[2] = 180;
}

void moving(int x, int y, int z) {
	zero_matrix();
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
	mull();
}

void scaling(float s) {
	zero_matrix();
	int x_centre, y_centre, z_centre;
	centre(x_centre, y_centre, z_centre);
	matrix[0][0] = matrix[1][1] = matrix[2][2] = s;
	matrix[3][0] = x_centre * (1 - s);
	matrix[3][1] = y_centre * (1 - s);
	matrix[3][2] = z_centre * (1 - s);
	mull();
}

void turn(float x, float y, float z)
{
	zero_matrix();
	int x_centre, y_centre, z_centre;
	centre(x_centre, y_centre, z_centre);

	if (x != 0)
	{
		matrix[1][1] = matrix[2][2] = (float)cos(x * M_PI / 180);
		matrix[1][2] = (float)sin(x * M_PI / 180);
		matrix[2][1] = (float)-sin(x * M_PI / 180);

		matrix[3][1] = y_centre * (1 - (float)cos(x * M_PI / 180)) + z_centre * (float)sin(x * M_PI / 180);
		matrix[3][2] = z_centre * (1 - (float)cos(x * M_PI / 180)) - y_centre * (float)sin(x * M_PI / 180);
	}

	if (y != 0)
	{
		matrix[0][0] = matrix[2][2] = (float)cos(y * M_PI / 180);
		matrix[0][2] = (float)-sin(y * M_PI / 180);
		matrix[2][0] = (float)sin(y * M_PI / 180);

		matrix[3][0] = x_centre * (1 - (float)cos(y * M_PI / 180)) - z_centre * (float)sin(y * M_PI / 180);
		matrix[3][2] = z_centre * (1 - (float)cos(y * M_PI / 180)) + x_centre * (float)sin(y * M_PI / 180);
	}

	if (z != 0)
	{
		matrix[0][0] = matrix[1][1] = (float)cos(z * M_PI / 180);
		matrix[0][1] = (float)sin(z * M_PI / 180);
		matrix[1][0] = (float)-sin(z * M_PI / 180);

		matrix[3][0] = x_centre * (1 - (float)cos(z * M_PI / 180)) + y_centre * (float)sin(z * M_PI / 180);
		matrix[3][1] = y_centre * (1 - (float)cos(z * M_PI / 180)) - x_centre * (float)sin(z * M_PI / 180);
	}

	mull();
}

void mull()
{
	float buf[4], buf1[4];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 4; j++)
			buf1[j] = 0;

		buf[0] = (float)x[i];
		buf[1] = (float)y[i];
		buf[2] = (float)z[i];
		buf[3] = 1;

		for (int k = 0; k < 4; k++)
			for (int t = 0; t < 4; t++)
				buf1[k] += buf[t] * matrix[t][k];

		x[i] = (int)buf1[0];
		y[i] = (int)buf1[1];
		z[i] = (int)buf1[2];
	}
}

void zero_matrix()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
}

void centre(int & x_centre, int & y_centre, int & z_centre)
{
	x_centre = 0;
	y_centre = 0;
	z_centre = 0;
	for (int i = 0; i < M; i++)
	{
		x_centre += x[i];
		y_centre += y[i];
		z_centre += z[i];
	}
	x_centre /= M;
	y_centre /= M;
	z_centre /= M;
}
