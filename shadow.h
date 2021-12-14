#pragma once
#include"parametrs.h"

void shadow(HDC dc);
void paint(HDC dc, int i1, int i2, int coordx[], int coordy[]);

void shadow(HDC dc) {
	int A = (yPl[1] - yPl[0]) * (zPl[2] - zPl[0]) - (yPl[2] - yPl[0]) * (zPl[1] - zPl[0]);
	int B = (zPl[1] - zPl[0]) * (xPl[2] - xPl[0]) - (zPl[2] - zPl[0]) * (xPl[1] - xPl[0]);
	int C = (xPl[1] - xPl[0]) * (yPl[2] - yPl[0]) - (xPl[2] - xPl[0]) * (yPl[1] - yPl[0]);
	int D = -(A * xPl[0] + B * yPl[0] + C * zPl[0]);

	int m = xLight - x[0];
	int n = yLight - y[0];
	int p = zLight - z[0];

	int xSh[M], ySh[M], zSh[M];

	for (int i = 0; i < M; i++)
	{
		float t = (float)(-A * x[i] - B * y[i] - C * z[i] - D) / (A * m + B * n + C * p);

		xSh[i] = m * t + x[i];
		ySh[i] = n * t + y[i];
		zSh[i] = p * t + z[i];
	}

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(255, 255, 255));

	MoveToEx(dc, xSh[0], ySh[0], NULL);
	LineTo(dc, xSh[1], ySh[1]);
	LineTo(dc, xSh[2], ySh[2]);
	LineTo(dc, xSh[3], ySh[3]);
	LineTo(dc, xSh[0], ySh[0]);

	MoveToEx(dc, xSh[4], ySh[4], NULL);
	LineTo(dc, xSh[5], ySh[5]);
	LineTo(dc, xSh[6], ySh[6]);
	LineTo(dc, xSh[7], ySh[7]);
	LineTo(dc, xSh[4], ySh[4]);

	MoveToEx(dc, xSh[0], ySh[0], NULL);
	LineTo(dc, xSh[4], ySh[4]);

	MoveToEx(dc, xSh[1], ySh[1], NULL);
	LineTo(dc, xSh[5], ySh[5]);

	MoveToEx(dc, xSh[2], ySh[2], NULL);
	LineTo(dc, xSh[6], ySh[6]);

	MoveToEx(dc, xSh[3], ySh[3], NULL);
	LineTo(dc, xSh[7], ySh[7]);

	paint(dc, 0, 8, xSh, ySh);

	// Треугольная призма
	MoveToEx(dc, xSh[8], ySh[8], NULL);
	LineTo(dc, xSh[9], ySh[9]);
	LineTo(dc, xSh[10], ySh[10]);
	LineTo(dc, xSh[11], ySh[11]);
	LineTo(dc, xSh[8], ySh[8]);

	MoveToEx(dc, xSh[10], ySh[10], NULL);
	LineTo(dc, xSh[12], ySh[12]);
	LineTo(dc, xSh[13], ySh[13]);
	LineTo(dc, xSh[11], ySh[11]);

	MoveToEx(dc, xSh[8], ySh[8], NULL);
	LineTo(dc, xSh[13], ySh[13]);

	MoveToEx(dc, xSh[9], ySh[9], NULL);
	LineTo(dc, xSh[12], ySh[12]);

	paint(dc, 8, 14, xSh, ySh);
}

void paint(HDC dc, int i1, int i2, int coordx[], int coordy[])
{
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(200, 200, 200));

	int x_max = coordx[i1], x_min = coordx[i1];
	int y_max = coordy[i1], y_min = coordy[i1];

	for (int i = i1; i < i2; i++)
	{
		if (x_max < coordx[i])
			x_max = coordx[i];

		if (x_min > coordx[i])
			x_min = coordx[i];

		if (y_max < coordy[i])
			y_max = coordy[i];

		if (y_min > coordy[i])
			y_min = coordy[i];
	}

	bool flag1 = 0, flag2 = 0;
	for (int y = y_min; y <= y_max; y++)
	{
		int x1 = x_min;
		int x2 = x_max;
		while (!flag1 || !flag2)
		{
			if (flag1 == 0)
				if (GetPixel(dc, x1, y) == RGB(255, 255, 255))
					flag1 = 1;
				else
					x1++;
			if (flag2 == 0)
				if (GetPixel(dc, x2, y) == RGB(255, 255, 255))
					flag2 = 1;
				else
					x2--;
			if (x1 == x2)
				break;
		}
		MoveToEx(dc, x1, y, NULL);
		LineTo(dc, x2 + 1, y);
		flag1 = 0;
		flag2 = 0;
	}

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(255, 255, 255));
}