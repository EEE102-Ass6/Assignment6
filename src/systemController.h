#pragma once
//Used to connect the mode layer and view layer
#include <iostream>
#include <string>
#include <fstream>
#include "systemController.h"
#include "(File)_header.h"// two class: driver_file and vehicle_file
#include "(Vehicle)_header.h"
#include "(Driver)_header.h"
#include "(Linkage)_header.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <regex>
#include <string>
#include "windows.h"
#include <iostream>
#include <fstream>

#define file_name_p "password.txt"
#ifndef _SYSTEMCONTROLLER
#define _SYSTEMCONTROLLER

class systemController

{
private:
	void noteHistory(std::string info);

	long lastIdNumber = 10000;

	bool isTelephone(char * tele);

	std::string time_ret();

	bool hasVehicle(char * lp);

protected:

	Driver_File *driverList = new Driver_File; //_file_d;

	Vehicle_File *vehicleList = new Vehicle_File;// _file_v;

	//int lastIdNumber = 100000;
	void Link_Set_Up();





public:
	systemController();

	bool searchKey(char * keys);// used to seach for a line infomation;

	bool addDriver(); // constructer of Diver. (string name, string gender, string age, ...) ask and anwer format.

	bool addVehicle(); // constructer of Vehicle class.(string tample, string carNumber, int ...) ask and answer format.

	void vehicleListAll();

	void driverListAll();

	void vehicleListAvaliable(); // call this fucntion when adding new vehicle

	void driverListAvaliable(); // call this function when adding new diver to divide

	bool modifyVehicle(); //

	bool modifyDriver(); //

	bool driverDelete(); // string pk is the primary key of the diver items

	bool vehicleDelete(); //  string pk is the primary key of the vehicle items;

	void DeleteAllVehicle(); //

	void DeleteAllDriver();//

	void showEditingRecords();

	void deleteHistory();

	bool canAddDriver(Vehicle *, user_info *);

	bool canAddVehicle(Driver *, car_info *);

	void User_Link(Driver &obj);

	void Car_Link(Vehicle &obj);

	void doRewardsAndPunishiment();

	void punishment(Driver * objectDriver);

	void reward(Driver * objectDriver);

	void payment();

	~systemController();

	//functional self-defined functions:

	long int the_Last_Number();
	
	void everything_Reset();

	

	char* readPassword(void);
	//void changePassword(void);
	void changePassword(char *new_password);
};
	

#endif