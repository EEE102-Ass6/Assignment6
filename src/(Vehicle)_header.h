#pragma once

#ifndef _VEHICLE
#define _VEHICLE

//header files:
#include "(Linkage)_header.h"

struct car_info {
	//vehicle type
	char vehicle_type[15];
	//the position in file:
	int position_in_file;
	//the linkage:
	link Vehicle_link[2];
	//Payment
	int Payment = 100;
	//Distance
	int Distance = 100;
};	//what we read from the file.

	//class:
class Vehicle {
private:

public:
	//constructor:
	Vehicle();
	Vehicle(car_info *temp);

public:
	void set_Veh(car_info *vehicle);
	void Pilot_Delete(char *driver_Num);

	void browse_Veh();	//browse.
	void pilot_Change(char *dn);

public:
	car_info* Get_info() { return &this->vehicle; };
	void payment(int distance);
	bool canAddDriver();
private:
	//basic infomation:
	car_info vehicle;
};

#endif