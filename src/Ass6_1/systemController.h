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

#ifndef _SYSTEMCONTROLLER
#define _SYSTEMCONTROLLER

class systemController

{
public:
	void noteHistory(std::string info);
	int lastIdNumber = 000000;
	bool isTelephone(char * tele);

protected:

	Driver_File *driverList = new Driver_File; //_file_d;

	Vehicle_File *vehicleList = new Vehicle_File;// _file_v;
  Driver *dr;
public:
  
	void Link_Set_Up();

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

	//functional self-defined functions:
  void punishment();
  void reward();
  //void show_money();
};

#endif