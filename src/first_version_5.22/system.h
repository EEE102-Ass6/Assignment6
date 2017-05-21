#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include<cstring>
#include <iostream>
#include "Screen.h"
#include "Var_whole.h"
DWORD WINAPI thread_Screen(LPVOID pM);
DWORD WINAPI thread_SystemCMD(LPVOID pM);
#endif