#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "parametrs.h"
#include "base.h"
#include"warnock.h"

using namespace std;

int main()
{
	initialization();
	warnock();
	do
	{
		switch (_getch())
		{
// перемещение фигуры 
		case'w': //вверх
			moving(0, -10, 0);
			break;
		case'a': //влево
			moving(-10, 0, 0);
			break;
		case's': //вниз
			moving(0, 10, 0);
			break;
		case'd': //вправо
			moving(10, 0, 0);
			break;
// поднятие фигуры вверх и вниз
		case '+': 
			moving(0, 0, 10);
			break;
		case '-': 
			moving(0, 0, -10);
			break;
// увеличение и уменьшение фигуры
		case'*':
			scaling(1.1);
			break;
		case'/': 
			scaling(0.9);
			break;
// поворот фигуры
		case'x': // по OX против часовой
			turn(5, 0, 0);
			break;
		case'X': // по OX по часовой
			turn(-5, 0, 0);
			break;
		case'Y': // по OY по часовой
			turn(0, 5, 0);
			break;
		case'y': // по OY против часовой
			turn(0, -5, 0);
			break;
		case'Z': // по OZ по часовой
			turn(0, 0, 5);
			break;
		case'z': // по OZ против часовой
			turn(0, 0, -5);
			break;
		default:
			return 0;
		}
		warnock();
	} while (1);
}
