#pragma once
#define M 14 //  оличество вершин
#define N 11 //  оличество многоугольников
//максимальное разрешение окна
#define I 1080 
#define J 600
//количество плоскостей
#define P 42

#include <Windows.h>
#include <iostream>
#include <vector>

//массив размером 1x3, который содержит начало координат окна и его размер в форме (’нач, ”нач, –азмер)
class window {
public:
	int x;
	int y;
	int size;
	window(int x, int y, int s) : x(x), y(y), size(s) {}
	window() : x(0), y(0), size(0) {}
};

struct mnogougilnik {
	int index;
	int count;
	COLORREF color;
	int A, B, C, D;
	int x_min, x_max, y_min, y_max;
};

struct vershina
{
	int x, y, z;
};

int x[M], y[M], z[M]; // параметры фигуры
float matrix[4][4]; // матрица изменени€ положени€

//источник света
int xLight;
int yLight;
int zLight;

//точки плоскасти, на которую падает тень
int xPl[3], yPl[3], zPl[3];

vershina versh[P];
mnogougilnik mnogo[N];