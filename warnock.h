#pragma once
#include"warnock_base.h"
#include"shadow.h"

using namespace std;

bool overallZize(int i, window win);
int coverage(window win);
void visualization(HDC dc, window win, COLORREF color);
int visibility(int pointX, int pointY, int P1x, int P1y, int P2x, int P2y);
int calculate(int i, window win);

void warnock();

void warnock() {
	setVershina();
	setMnogougilnik();

	system("cls");
	COLORREF back = RGB(13, 13, 13);
	vector<window> stack;

	int x_min, x_max;
	int y_min, y_max;
	x_max = versh[0].x;
	x_min = versh[0].x;
	y_min = versh[0].y;
	y_max = versh[0].y;
	for (int i = 0; i < P; i++)
	{
		if (x_min > versh[i].x)
			x_min = versh[i].x;
		if (x_max < versh[i].x)
			x_max = versh[i].x;
		if (y_min > versh[i].y)
			y_min = versh[i].y;
		if (y_max < versh[i].y)
			y_max = versh[i].y;
	}
	int max = (x_max - x_min + 1);
	if (y_max - y_min + 1 > max)
		max = y_max - y_min + 1;

	HWND hwnd = GetConsoleWindow();
	HDC dc = GetDC(hwnd);

	HDC memDC = CreateCompatibleDC(dc);
	HBITMAP memBM = CreateCompatibleBitmap(dc, I, J);
	SelectObject(memDC, memBM);

	window win(x_min, y_min, max);
	bool vneshnost;

	stack.push_back(win);
	while (stack.size() != 0)
	{
		win = stack.back();
		stack.pop_back();
		vneshnost = false;

		int i = 0;
		while (i <= N && vneshnost == false)
		{
			vneshnost = overallZize(i, win);
			i++;
		}

		if (vneshnost)
		{
			if (win.size > 1)
			{
				win.size = win.size / 2 + win.size % 2;
				stack.push_back(window(win.x + win.size, win.y + win.size, win.size));
				stack.push_back(window(win.x, win.y + win.size, win.size));
				stack.push_back(window(win.x + win.size, win.y, win.size));
				stack.push_back(window(win.x, win.y, win.size));
			}
			else
			{
				int n = coverage(win);
				if (n >= 0)
				{
					visualization(memDC, win, mnogo[n].color);
				}
				else
				{
					//visualization(memDC, win, back);
				}
			}
		}
		else
		{
			//visualization(memDC, win, back);
		}
	}

	shadow(memDC);

	BitBlt(dc, 0, 0, I, J, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}

//подпрограмма реализации простого габаритного теста с пр€моугольной оболочкой
bool overallZize(int i, window win) {
	int xLeft, xRight, yUp, yDown;
	xLeft = win.x;
	xRight = win.x + win.size - 1;
	yUp = win.y;
	yDown = win.y + win.size - 1;

	bool buf = true;

	if (mnogo[i].x_min > xRight) return false;
	if (mnogo[i].x_max < xLeft) return false;
	if (mnogo[i].y_max < yUp) return false;
	if (mnogo[i].y_min > yDown) return false;

	return true;
}

//подпрограмма визуализации окна 
void visualization(HDC dc, window win, COLORREF color) {
	for (int j = win.y; j < win.y + win.size; j++)
		for (int i = win.x; i < win.x + win.size; i++)
			SetPixel(dc, i, j, color);
}

//подпрограмма, провер€юща€, покрывает ли многоугольник центр окна 
int coverage(window win) {
	int z_max = versh[0].z;
	for (int i = 0; i < P; i++)
	{
		if (z_max > versh[i].z)
			z_max = versh[i].z;
	}
	int number = -1;
	int vidimost;
	int pointX = win.x + win.size / 2;
	int pointY = win.y + win.size / 2;
	int T1x, T1y, T2x, T2y;
	int index;
	bool flag;


	for (int i = 0; i < N; i++)
	{
		flag = true;
		index = mnogo[i].index;

		for (int j = 1; j < mnogo[i].count; j++)
		{
			T1x = versh[index].x;
			T1y = versh[index].y;
			T2x = versh[index + 1].x;
			T2y = versh[index + 1].y;
			vidimost = visibility(pointX, pointY, T1x, T1y, T2x, T2y);
			if (vidimost < 0) flag = false;
			index++;
		}

		if (flag)
		{
			T1x = versh[index].x;
			T1y = versh[index].y;
			T2x = versh[mnogo[i].index].x;
			T2y = versh[mnogo[i].index].y;
			vidimost = visibility(pointX, pointY, T1x, T1y, T2x, T2y);
			if (vidimost >= 0)
			{
				int z = calculate(i, win);
				if (z > z_max)
				{
					z_max = z;
					number = i;
				}
			}
		}

	}

	return number;
}

//подпрограмма вычислени€ видимости точки
int visibility(int pointX, int pointY, int P1x, int P1y, int P2x, int P2y) {
	int R1 = (pointX - P2x) * (P1y - P2y);
	int R2 = (pointY - P2y) * (P1x - P2x);
	int R = R1 - R2;

	if (R > 0) return 1;
	else if (R == 0) return 0;
	else return -1;
}

//подпрограмма вычислени€ интенсивности пиксела 
int calculate(int i, window win) {
	int XCentre = win.x + win.size / 2;
	int YCentre = win.y + win.size / 2;
	int z = versh[i].z;
	for (int j = 0; j < mnogo[i].count; j++)
	{
		if (z > versh[j].z)
			z = versh[j].z;
	}
	if (mnogo[i].C == 0)
		for (int j = 1; j < mnogo[i].count - 1; j++)
		{
			if (z < versh[j].z)
				z = versh[j].z;
			if (z < versh[j + 1].z)
				z = versh[j + 1].z;
		}
	else
	{
		int A = mnogo[i].A;
		int B = mnogo[i].B;
		int C = mnogo[i].C;
		int D = mnogo[i].D;
		z = -(A * XCentre + B * YCentre + D) / C;
	}

	return z;
}

