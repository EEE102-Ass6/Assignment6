#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <string.h>
#include<cstring>
#include  <fstream>
#include <windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <sys\stat.h>
#include <io.h>
#include <iostream>
#include "Screen.h"
#include "Var_whole.h"
#include "systemController.h"
using namespace std;
DWORD WINAPI thread_Screen(LPVOID pM);
DWORD WINAPI thread_SystemCMD(LPVOID pM);
char* szFilePath(string txt);
int szFileSize(string sFileName);
#endif