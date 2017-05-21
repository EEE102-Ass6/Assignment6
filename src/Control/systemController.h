#pragma once
//Used to connect the mode layer and view layer
#include <iostream>
#include <string>
#include <fstream>
#include "systemController.h"
#include "File.h"// two class: driver_file and vehicle_file;
#include "Vehicle.h"
#include "Driver.h"
#include "(Linkage).h"

using namespace std;

class systemController

{
private:
	void noteHistory(std::string info);


protected:

	driver_file *driverList;

	vehicle_file *vehicleList;

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

	//void showEditingRecords();

	/*void regPayment(); //

	void regRewards(); //

	void regPunishment(); */

	bool driverDelete(); // string pk is the primary key of the diver items

	bool vehicleDelete(); //  string pk is the primary key of the vehicle items;

	void DeleteAllVehicle(); //

	void DeleteAllDriver();//

	void showEditingRecords();

	void deleteHistory();

	void changeSudoPassword(char *psw);

	char *getUserPassword();

	~systemController();
};
