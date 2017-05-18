#pragma once
//Used to connect the mode layer and view layer
#include <iostream>
#include <string>
#include "systemController.h"
#include "Diver.h"
#include "Vehicle.h"

using namespace std;

class systemController
{
protected:
	
	Diver *diver;

	Vehicle *vehicle;

public:
	systemController();

	void searchKey(string keys);// used to seach for a line infomation;
	
	bool addDirver(); // constructer of Diver. (string name, string gender, string age, ...) ask and anwer format.

	bool addVehicle(); // constructer of Vehicle class.(string tample, string carNumber, int ...) ask and answer format.

	void vehicleListAll(); 

	void diverListAll();

	void vehicleListAvaliable(); // call this fucntion when adding new vehicle

	void diverListAvaliable(); // call this function when adding new diver to divide 

	bool modifyVehicle(); // 

	bool modifyDiver(); // 

	void noteHistory(); // 

	void regPayment(); // 

	void regRewards(); // 

	void regPunishment(); // 

	void diverDelete(); // string pk is the primary key of the diver items

	void vehicleDelete(); //  string pk is the primary key of the vehicle items;

	void DeleteAllVehicle(); //

	void DeleteAllDiver();//

	~systemController();
};

