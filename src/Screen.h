#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  

//Get the currecnt pointer//
void get_NowCursor();

//Get the currecnt pointer//
void get_NowCursor_Start();

//Go to the set position//
void gotoxy(int x, int y);

#endif