#pragma once
#ifndef VAR_WHOLE_H
#define VAR_WHOLE_H
#include <Windows.h>
#include <cstring>
#include "systemController.h"
extern int point_X;
extern int point_Y;
extern int point_A;
extern int point_B;
extern bool thread_check;
extern HANDLE handle;
extern HANDLE handle_sys;
extern int check_command;
extern char input_check[30];
extern int check_file_driver;
extern int check_file_vehicle;
extern int check_file_history;
//extern systemController *sc;
#endif // VAR_WHOLE_H