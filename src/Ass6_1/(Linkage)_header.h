#pragma once

#ifndef _LINKAGE
#define _LINKAGE

//header files:
#include <windows.h>

extern int sizeof_driver_file;
extern int sizeof_vehicle_file;

#define file_name_d "driver"
#define file_name_v "vehicle"

struct link {
	//driver's number:
  char driver_Num[15];// ={ NULL };
	//license plate:
  char license_plate[15]; //= { NULL };
};

struct reward
{

};

char* Random_License(void);

#endif

/*
1. driving the car overloading than 20%.
2. over speeding.
3. deliberately block the number plate.
4.
5. driving without the specific license.
6. Drunk driving.
7. escape after a traffic accident.
*/