//source file (driver):

using namespace std;

//header files:
#include <iostream>
#include "(Driver)_header.h"

//constructor:
Driver::Driver() {	/*initialization*/
					//link content:
	memset(user.Driver_link.driver_Num, '\0', 15);
	strcpy(this->user.Driver_link.driver_Num, "No_Number");
	memset(user.Driver_link.license_plate, '\0', 15);
	strcpy(this->user.Driver_link.license_plate, "No_Vehicle");

	//other infomation:
	this->user.Driver_Sex = 0;
	strcpy(this->user.Driver_Name, "No_Name");		//initialization of name.
	strcpy(this->user.Driver_Tel, "13800000000");	//initialization of tele.

													//position in file:
	this->user.position_in_file = sizeof_driver_file;
}
Driver::Driver(user_info *temp) {
	/*according to a struct*/
	//initialization:
	memset(user.Driver_link.driver_Num, '\0', 15);
	memset(user.Driver_link.license_plate, '\0', 15);

	//link content:
	if (strcmp((temp->Driver_link.driver_Num), "No_Number") != 0) {
		strcpy(this->user.Driver_link.driver_Num, temp->Driver_link.driver_Num);
	}
	else
		strcpy(this->user.Driver_link.driver_Num, "No_Number");

	if (strcmp((temp->Driver_link.license_plate), "No_Vehicle") != 0)
		strcpy(this->user.Driver_link.license_plate, temp->Driver_link.license_plate);
	else
		strcpy(this->user.Driver_link.license_plate, "No_Vehicle");

	//others (must required!):
	this->user.Driver_Sex = temp->Driver_Sex;
	strcpy(this->user.Driver_Name, temp->Driver_Name);
	strcpy(this->user.Driver_Tel, temp->Driver_Tel);

	//position in file:
	this->user.position_in_file = temp->position_in_file;

	this->user.money = temp->money;
}

//browse:
void Driver::browse_Driver() {
	cout << "The driver information is shown as below" << endl;
	//basic info:
	cout << this->user.Driver_Name << "\t\t";
	if (this->user.Driver_Sex)
		cout << "male" << '\t';
	else if (!this->user.Driver_Sex)
		cout << "female" << '\t';
	cout << this->user.Driver_Tel << '\t';

	//link info:
	if (user.Driver_link.driver_Num == NULL ||
		strlen(user.Driver_link.driver_Num) == 0 ||
		!strcmp(user.Driver_link.driver_Num, "No_Number")) {
		cout << "No driver number!" << '\t';
	}
	else
		cout << user.Driver_link.driver_Num << '\t';
	if (user.Driver_link.license_plate == NULL ||
		strlen(user.Driver_link.license_plate) == 0 ||
		!strcmp(user.Driver_link.license_plate, "No_Vehicle")) {
		cout << "No vehicle!" << '\t';
	}
	else {	
		cout << user.Driver_link.license_plate << '\t';
	}
	cout << "\tMoney: " << this->user.money << endl;

	//other info...
	cout << "position in file: " << user.position_in_file << endl;

	//std::system("PAUSE");
}

void Driver::car_Change(char *lp) {
	strcpy(this->user.Driver_link.license_plate, lp);
}

//set the driver
void Driver::set_User(user_info *target) {
	strcpy(user.Driver_Name, target->Driver_Name);
	strcpy(user.Driver_Tel, target->Driver_Tel);

	user.Driver_Sex = target->Driver_Sex;
}

void Driver::Car_Delete(char *license_plate) {
	memset(user.Driver_link.license_plate, '\0', 15);
	strcpy(user.Driver_link.license_plate, "No_Vehicle");
}

void Driver::punishment_Driver(int num) {
	//user_info *driver = new user_info;
	PUNISHMENT d;
	switch (num) {
	case 1: d = Driving_the_bus_overloading_more_than_20; break;
	case 2: d = Over_speeding; break;
	case 3: d = Deliberately_block_the_number_plate; break;
	case 4: d = Deliberately_stop_in_the_expressway_lane; break;
	case 5: d = Continuous_driving_medium_sized_passenger_car_dangerous_goods_transport_vehicles_more_than_4_hours_without_stopping_or_parking_rest_time_less_than_20_minutes;
		break;
	case 6: d = Driving_school_bus_without_getting_the_specific_license; break;
	case 7: d = Drunk_driving; break;
	case 8: d = Escape_after_a_traffic_accident; break;
	default: break;
	}
	//cout << "Punishment is " << d << "гд" << endl;
	std::cout << user.money << std::endl;
	std::cout << d << std::endl;
	this->user.money -= (int)d;// struc
	std::cout << user.money << std::endl;
	std::cout << d << std::endl;
	//cout << "The totally money is " << this->Get_info()->money << "гд" << endl;
	//cout << ""
	//return d;
}
bool Driver::canAddVehicle()
{
	if (strcmp(this->user.Driver_link.license_plate, "No_Vehicle") == 0) {
		return true;
	}
	return false;
}
void Driver::reward_Driver(int num) {
	//user_info *driver = new user_info;
	REWARD d;
	switch (num) {
	case 1: d = Take_care_of_the_overall_situation_the_interests_of_the_company_as_a_matter_of_dedication; break;
	case 2: d = vehicles_parked_after_safe_and_safekeeping_measures; break;
	case 3: d = minutes_before_the_arrival_of_the_guests_to_the_guard; break;
	case 4: d = Arrangements_for_easy_driving_routes_not_out_of_time_for_private_affairs; break;
	case 5: d = Continue_to_enhance_business_learning_self_improvement; break;
	case 6: d = Good_braking_effect; break;
	case 7: d = No_maintenance_shop_to_ask_for_any_property_of_the_phenomenon; break;
	case 8: d = Vehicles_on_request_self_study_self_repair; break;
	default:
		break;
	}
	//c//out << "Reward is " << d << "гд" << endl;
	//int money;
	this->user.money += d;
	//cout << "The totally money is " << this->Get_info()->money << "гд" << endl;
	//cout << driver->money;
	//cout << ""
	//return d;
}