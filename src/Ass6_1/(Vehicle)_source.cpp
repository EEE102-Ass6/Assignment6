//source file (vehicle):

using namespace std;

//header file:
#include <string>
#include <iostream>
#include "(Vehicle)_header.h"

//constructor:
Vehicle::Vehicle() {	/*initialization*/
						//link content (a couple of linkage is equiped!):
	strcpy(this->vehicle.Vehicle_link[0].driver_Num, "1_No_Pilot");
	strcpy(this->vehicle.Vehicle_link[1].driver_Num, "2_No_Pilot");

	strcpy(this->vehicle.Vehicle_link[0].license_plate, "No_Plate");
	strcpy(this->vehicle.Vehicle_link[1].license_plate, "No_Plate");

	//others:
	strcpy(this->vehicle.vehicle_type, "Unknown_Type");

	//position in file:
	this->vehicle.position_in_file = sizeof_vehicle_file;
}
Vehicle::Vehicle(car_info *temp) {	/*according to a struct*/
									//link content (a couple of linkage is equiped!):
	strcpy(this->vehicle.Vehicle_link[0].driver_Num, temp->Vehicle_link[0].driver_Num);	//ten 'zeros'!
	strcpy(this->vehicle.Vehicle_link[1].driver_Num, temp->Vehicle_link[1].driver_Num);	//ten 'zeros'!

	strcpy(this->vehicle.Vehicle_link[0].license_plate, temp->Vehicle_link[0].license_plate);
	strcpy(this->vehicle.Vehicle_link[1].license_plate, temp->Vehicle_link[1].license_plate);

	//others:
	strcpy(this->vehicle.vehicle_type, temp->vehicle_type);

	//position in file:
	this->vehicle.position_in_file = temp->position_in_file;
}

/*--------------------------------------------------*/

//browse information
void Vehicle::browse_Veh() {
	cout << "The vehicle information is shown as below" << endl;

	//license_plate:
	cout << vehicle.Vehicle_link[0].license_plate << endl;

	//pilot(s):
	for (int i = 0; i < 2; i++) {
		cout << i + 1 << ": " << vehicle.Vehicle_link[i].driver_Num << endl;
	}

	//other info...
	cout << vehicle.vehicle_type << endl;
	cout << "position in file: " << vehicle.position_in_file << endl;
}

void Vehicle::set_Veh(car_info* target) {
	//link content (a couple of linkage is equiped!):
	strcpy(this->vehicle.Vehicle_link[0].driver_Num, target->Vehicle_link[0].driver_Num);
	strcpy(this->vehicle.Vehicle_link[1].driver_Num, target->Vehicle_link[1].driver_Num);

	strcpy(this->vehicle.Vehicle_link[0].license_plate, target->Vehicle_link[0].license_plate);
	strcpy(this->vehicle.Vehicle_link[1].license_plate, target->Vehicle_link[1].license_plate);

	//others:
	strcpy(this->vehicle.vehicle_type, target->vehicle_type);
}

void Vehicle::Pilot_Delete(char *driver_Num) {
	for (int i = 0; i < 2; i++)
		if (!strcmp(vehicle.Vehicle_link[i].driver_Num, driver_Num))
			strcpy(vehicle.Vehicle_link[i].driver_Num, NULL);
}

//modify:
void Vehicle::modify_Veh(Vehicle &Vehicle, car_info *target) {
	//cout << "Do you want to"
	system("cls");
	cout << "********modify vehicle***********" << endl;
	cout << "please input the vehicle number" << endl;
	int n;
	cin >> n;

	/*
	for (int k = 0; k < 100; k++) {	//for multiple vehicles

	//unknown...

	if (n == vehicle.Driver_link.vehicle_Num) {
	Vehicle.browse_Veh(target);
	cout << "Are you sure to change the vehicle's information Y|N" << endl;
	char x;
	cin >> x;
	if (x == 'Y' || x == 'y') {
	cout << "which one do you want to change" << endl;
	cout << "1. vehicle number" << endl;
	cout << "2. vehicle license" << endl;
	cout << "3. vehicle type" << endl;
	int n;
	cin >> n;
	while (n < 1 || n > 3) {
	cout << "error input!!! please input again" << endl;
	cin >> n;
	}
	switch (n)
	{
	case 1: {
	cout << "please input vehicle number:" << endl;
	int n1;
	cin >> n1;

	//target->num[k] = n1;

	Vehicle.Set_Veh(target);
	break;
	}
	case 2: {
	cout << "please input vehicle license:" << endl;
	char s1;
	cin >> s1;
	target->license_plate[k] = s1;
	Vehicle.Set_Veh(target);
	break;
	}
	case 3: {
	cout << "please input vehicle Type:" << endl;
	char s2;
	cin >> s2;
	target->vehicle_type[k] = s2;
	Vehicle.Set_Veh(target);
	break;
	}
	default:
	break;
	}
	}
	}
	}
	*/
}

//add pilot:
void Vehicle::add_Veh(car_info *target) {
	system("cls");
	int n;
	cout << "********add vehicle's information" << endl;
	char s1, s2;
	cout << "please input vehicle number:" << endl;
	cin >> n;

	//target->num[n] = n;

	/*
	cout << "please input vehicle license:" << endl;
	cin >> s1;
	target->license_plate[n] = s1;
	cout << "please input vehicle Type:" << endl;
	cin >> s2;
	target->vehicle_type[n] = s2;
	cout << "successful add!!!" << endl;
	*/
}