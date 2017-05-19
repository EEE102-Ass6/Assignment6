#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  

void get_NowCursor();
/*{
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	point_X = bInfo.dwCursorPosition.X;
	point_Y = bInfo.dwCursorPosition.Y;
}*/

void get_NowCursor_Start();
/*{
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	point_A = bInfo.dwCursorPosition.X;
	point_B = bInfo.dwCursorPosition.Y;
}*/

void gotoxy(int x, int y);
/*{
	COORD c = { x, y };
	SetConsoleCursorPosition(hOut, c);
}*/
#endif