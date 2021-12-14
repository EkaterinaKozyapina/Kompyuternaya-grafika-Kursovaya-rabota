#pragma once
#include"parametrs.h"

void setVershina();
void setOneVershina(int & i, int p1, int p2, int p3, int p4 = -1);
void setMnogougilnik();
void setOneMnogougilnik(int i, int j, int count, COLORREF color);

void setVershina() {
	int i = 0;
	setOneVershina(i, 0, 1, 2, 3);
	setOneVershina(i, 7, 6, 5, 4);
	setOneVershina(i, 4, 5, 1, 0);
	setOneVershina(i, 3, 2, 6, 7);
	setOneVershina(i, 0, 3, 7, 4);
	setOneVershina(i, 1, 5, 6, 2);
	setOneVershina(i, 8, 9, 10, 11);
	setOneVershina(i, 13, 12, 9, 8);
	setOneVershina(i, 11, 10, 12, 13);
	setOneVershina(i, 11, 13, 8);
	setOneVershina(i, 9, 12, 10);
}

void setOneVershina(int & i, int p1, int p2, int p3, int p4) {
	versh[i].x = x[p1];
	versh[i].y = y[p1];
	versh[i].z = z[p1];
	i++;
	versh[i].x = x[p2];
	versh[i].y = y[p2];
	versh[i].z = z[p2];
	i++;
	versh[i].x = x[p3];
	versh[i].y = y[p3];
	versh[i].z = z[p3];
	i++;
	if (p4 != -1)
	{
		versh[i].x = x[p4];
		versh[i].y = y[p4];
		versh[i].z = z[p4];
		i++;
	}
}

void setMnogougilnik() {
	int i = 0;
	setOneMnogougilnik(i, 0, 4, RGB(0, 0, 110));
	i++;
	setOneMnogougilnik(i, 4, 4, RGB(0, 110, 0));
	i++;
	setOneMnogougilnik(i, 8, 4, RGB(110, 0, 0));
	i++;
	setOneMnogougilnik(i, 12, 4, RGB(110, 110, 0));
	i++;
	setOneMnogougilnik(i, 16, 4, RGB(110, 0, 110));
	i++;
	setOneMnogougilnik(i, 20, 4, RGB(0, 110, 110));
	i++;
	setOneMnogougilnik(i, 24, 4, RGB(0, 0, 170));
	i++;
	setOneMnogougilnik(i, 28, 4, RGB(0, 170, 0));
	i++;
	setOneMnogougilnik(i, 32, 4, RGB(170, 0, 0));
	i++;
	setOneMnogougilnik(i, 36, 3, RGB(170, 170, 0));
	i++;
	setOneMnogougilnik(i, 39, 3, RGB(170, 0, 170));
}

void setOneMnogougilnik(int i, int j, int count, COLORREF color) {
	//указатель на первую вершину многоугольника в массиве Вершина
	mnogo[i].index = j;

	//число вершин многоугольника
	mnogo[i].count = count;

	//интенсивность света или цвет многоугольника
	mnogo[i].color = color;

	//коэффициенты a, b, c, d уравнения плоскости, несущей многоугольник
	int vec1[3], vec2[3];

	vec1[0] = versh[j + 1].x - versh[j].x;
	vec2[0] = versh[j + 2].x - versh[j].x;

	vec1[1] = versh[j + 1].y - versh[j].y;
	vec2[1] = versh[j + 2].y - versh[j].y;

	vec1[2] = versh[j + 1].z - versh[j].z;
	vec2[2] = versh[j + 2].z - versh[j].z;

	mnogo[i].A = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	mnogo[i].B = vec1[2] * vec2[0] - vec2[2] * vec1[0];
	mnogo[i].C = vec1[0] * vec2[1] - vec2[0] * vec1[1];
	mnogo[i].D = -(mnogo[i].A * versh[j].x + mnogo[i].B * versh[j].y + mnogo[i].C * versh[j].z);

	//габариты Xmin, Xmax, Ymin, Ymax прямоугольной объемлющей оболочки многоугольника
	int x_min, x_max;
	int y_min, y_max;
	x_max = versh[j].x;
	x_min = versh[j].x;
	y_min = versh[j].y;
	y_max = versh[j].y;
	for (int i = j; i < j + count; i++)
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
	mnogo[i].x_min = x_min;
	mnogo[i].x_max = x_max;
	mnogo[i].y_min = y_min;
	mnogo[i].y_max = y_max;
}