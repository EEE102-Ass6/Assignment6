#pragma once

#ifndef _VEHICLE
#define _VEHICLE

//header files:
#include "(Linkage)_header.h"

struct car_info {
	//vehicle type
  char vehicle_type[15]; //= { NULL };
	//the position in file:
	int position_in_file;
	//the linkage:
	link Vehicle_link[2];
};	//what we read from the file.

	//class:
class Vehicle {
public:
	//constructor:
	Vehicle();
	Vehicle(car_info *temp);

public:
	void set_Veh(car_info *vehicle);
	void Pilot_Delete(char *driver_Num);

	void browse_Veh();								//browse the information
	void modify_Veh(Vehicle &, car_info *vehicle);	//modify
	void add_Veh(car_info *vehicle);				//add the people

public:
	car_info* Get_info() { return &this->vehicle; };

private:
	//basic infomation:
	car_info vehicle;
};

#endif