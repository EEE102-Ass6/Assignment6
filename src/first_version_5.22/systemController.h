#pragma once
//Used to connect the mode layer and view layer
#include <iostream>
#include <string>
#include "systemController.h"
//#include "Diver.h"
//#include "Vehicle.h"

using namespace std;

class systemController
{
protected:

//	Driver *driver;

//	Vehicle *vehicle;

public:
	systemController() {};


	bool searchKey(char* keys) { return false; };// used to seach for a line infomation;

	bool addDriver(); // constructer of Diver. (string name, string gender, string age, ...) ask and anwer format.

	bool addVehicle(); // constructer of Vehicle class.(string tample, string carNumber, int ...) ask and answer format.

	void vehicleListAll();

	void driverListAll();

	void vehicleListAvaliable(); // call this fucntion when adding new vehicle

	void driverListAvaliable(); // call this function when adding new diver to divide

	bool modifyVehicle(); //

	bool modifyDriver(); //

	void showEdtingRecords(); //

	void regPayment(); //

	void regRewards(); //

	void regPunishment(); //

	void driverDelete(); // string pk is the primary key of the diver items

	void vehicleDelete(); //  string pk is the primary key of the vehicle items;

	void DeleteAllVehicle(); //

	void DeleteAllDriver();//

	~systemController() {};
};
