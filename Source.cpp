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
// ����������� ������ 
		case'w': //�����
			moving(0, -10, 0);
			break;
		case'a': //�����
			moving(-10, 0, 0);
			break;
		case's': //����
			moving(0, 10, 0);
			break;
		case'd': //������
			moving(10, 0, 0);
			break;
// �������� ������ ����� � ����
		case '+': 
			moving(0, 0, 10);
			break;
		case '-': 
			moving(0, 0, -10);
			break;
// ���������� � ���������� ������
		case'*':
			scaling(1.1);
			break;
		case'/': 
			scaling(0.9);
			break;
// ������� ������
		case'x': // �� OX ������ �������
			turn(5, 0, 0);
			break;
		case'X': // �� OX �� �������
			turn(-5, 0, 0);
			break;
		case'Y': // �� OY �� �������
			turn(0, 5, 0);
			break;
		case'y': // �� OY ������ �������
			turn(0, -5, 0);
			break;
		case'Z': // �� OZ �� �������
			turn(0, 0, 5);
			break;
		case'z': // �� OZ ������ �������
			turn(0, 0, -5);
			break;
		default:
			return 0;
		}
		warnock();
	} while (1);
}
