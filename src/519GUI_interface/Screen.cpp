#include "Screen.h"
#include "var_Whole.h"
extern HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
typedef int a;
typedef int b;
using namespace std;

void get_NowCursor()
{
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	point_X = bInfo.dwCursorPosition.X;
	point_Y = bInfo.dwCursorPosition.Y;
}

void get_NowCursor_Start()
{
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	point_A = bInfo.dwCursorPosition.X;
	point_B = bInfo.dwCursorPosition.Y;
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(hOut, c);
}