//source file (vehicle):

using namespace std;

//header file:
#include <string>
#include <iostream>
#include "(Vehicle)_header.h"

//constructor:
Vehicle::Vehicle() {	/*initialization*/
						//initialization:
	for (int i = 0; i < 2; i++) {
		memset(vehicle.Vehicle_link[i].driver_Num, '\0', 15);
		memset(vehicle.Vehicle_link[i].license_plate, '\0', 15);
	}

	//link content (a couple of linkage is equiped!):
	for (int i = 0; i < 2; i++) {
		strcpy(this->vehicle.Vehicle_link[i].driver_Num, "No_Pilot");
		strcpy(this->vehicle.Vehicle_link[i].license_plate, "No_Plate");
	}

	//others:
	memset(vehicle.vehicle_type, '\0', 15);
	strcpy(this->vehicle.vehicle_type, "Unknown_Type");

	//position in file:
	this->vehicle.position_in_file = sizeof_vehicle_file;
}
Vehicle::Vehicle(car_info *temp) {	/*according to a struct*/
									//initialization:
	for (int i = 0; i < 2; i++) {
		memset(vehicle.Vehicle_link[i].driver_Num, '\0', 15);
		memset(vehicle.Vehicle_link[i].license_plate, '\0', 15);
	}

	//link content (a couple of linkage is equiped!):
	for (int i = 0; i < 2; i++) {
		if (strcmp(temp->Vehicle_link[i].driver_Num, "No_Pilot") != 0)
			strcpy(this->vehicle.Vehicle_link[i].driver_Num, temp->Vehicle_link[i].driver_Num);
		else
			strcpy(this->vehicle.Vehicle_link[i].driver_Num, "No_Pilot");
	}

	for (int i = 0; i < 2; i++) {
		if (strcmp(temp->Vehicle_link[i].license_plate, "No_Plate") != 0)
			strcpy(this->vehicle.Vehicle_link[i].license_plate, temp->Vehicle_link[i].license_plate);
		else
			strcpy(this->vehicle.Vehicle_link[i].license_plate, "No_Plate");
	}

	//others:
	memset(vehicle.vehicle_type, '\0', 15);
	strcpy(this->vehicle.vehicle_type, temp->vehicle_type);
	this->vehicle.Distance = temp->Distance;
	this->vehicle.Payment = temp->Payment;

	//position in file:
	this->vehicle.position_in_file = temp->position_in_file;
}

/*--------------------------------------------------*/

//browse information
void Vehicle::browse_Veh() {
	cout << "The vehicle information is shown as below" << endl;

	//license_plate:
	if (strlen(vehicle.Vehicle_link[0].license_plate) == 0 ||
		!strcmp(vehicle.Vehicle_link[0].license_plate, "No_Plate"))
		cout << "No plate!" << "\t";
	else
		cout << vehicle.Vehicle_link[0].license_plate << "\t";

	//pilot(s):
	for (int i = 0; i < 2; i++) {
		cout << i + 1 << ": ";
		if (vehicle.Vehicle_link[i].driver_Num == NULL ||
			strlen(vehicle.Vehicle_link[i].driver_Num) == 0 ||
			!strcmp(vehicle.Vehicle_link[i].driver_Num, "No_Pilot")) {
			cout << "No pilot!" << "\t";
		}
		else
			cout << vehicle.Vehicle_link[i].driver_Num << "\t";
	}
	cout << "payment: " << vehicle.Payment << "\t";
	//other info...
	cout << vehicle.vehicle_type << endl;
	cout << "position in file: " << vehicle.position_in_file << endl;
}

void Vehicle::pilot_Change(char *dn) {
	for (int i = 0; i < 2; i++) {
		if (this->vehicle.Vehicle_link[i].driver_Num == NULL ||
			!strcmp(this->vehicle.Vehicle_link[i].driver_Num, "No_Pilot") ||
			strlen(this->vehicle.Vehicle_link[i].driver_Num) == 0) {
			strcpy(this->vehicle.Vehicle_link[i].driver_Num, dn);
			break;
		}
	}
}
//others:
void Vehicle::set_Veh(car_info* target) {
	//link content (a couple of linkage is equiped!):
	for (int i = 0; i < 2; i++) {
		strcpy(this->vehicle.Vehicle_link[i].driver_Num, target->Vehicle_link[i].driver_Num);
		strcpy(this->vehicle.Vehicle_link[i].license_plate, target->Vehicle_link[i].license_plate);
	}

	//others:
	strcpy(this->vehicle.vehicle_type, target->vehicle_type);
}

void Vehicle::Pilot_Delete(char *driver_Num) {
	for (int i = 0; i < 2; i++) {
		if (!strcmp(vehicle.Vehicle_link[i].driver_Num, driver_Num)) {
			strcpy(vehicle.Vehicle_link[i].driver_Num, "No_Pilot");
			break;
		}
	}
}

void Vehicle::payment(int distance) {
	//cout << this->vehicle.Payment << endl;
	if (distance >= 10) {
		this->vehicle.Payment += 14 + 2.4 * 7 + (distance - 10) * 3.6;
	}
	else if (distance >= 3) {
		this->vehicle.Payment += 14 + 2.4 * distance;
	}
	else {
		this->vehicle.Payment += 14;
	}
	//cout << this->vehicle.Payment << endl;
	//cout << this->vehicle.Distance << endl;
	this->vehicle.Distance += distance;
	//cout << this->vehicle.Distance << endl;
	//car->Payment
	//cout << "the total car distance is: " << this->vehicle.Distance << endl;
	//cout << "the total car payment is: " << this->vehicle.Payment << endl;
}

bool Vehicle::canAddDriver()
{
	for (int i = 0; i < 2; i++)
	{
		if (strcmp(this->vehicle.Vehicle_link[i].driver_Num, "No_Pilot") == 0)
		{
			return true;
		}
	}
	return false;
}
