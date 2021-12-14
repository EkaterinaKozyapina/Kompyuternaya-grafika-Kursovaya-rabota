#pragma once
#define M 14 // ���������� ������
#define N 11 // ���������� ���������������
//������������ ���������� ����
#define I 1080 
#define J 600
//���������� ����������
#define P 42

#include <Windows.h>
#include <iostream>
#include <vector>

//������ �������� 1x3, ������� �������� ������ ��������� ���� � ��� ������ � ����� (����, ����, ������)
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

int x[M], y[M], z[M]; // ��������� ������
float matrix[4][4]; // ������� ��������� ���������

//�������� �����
int xLight;
int yLight;
int zLight;

//����� ���������, �� ������� ������ ����
int xPl[3], yPl[3], zPl[3];

vershina versh[P];
mnogougilnik mnogo[N];