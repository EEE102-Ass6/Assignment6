/*vehicle
book information

function
1.modify
2.add
*/
#ifndef _VEHICLE
#define _VEHICLE
class Vehicle{
private:
	int num; //car number
	//int people_num;//people number
	std::string  license_plate;//license plate
	std::string  vehicle_type;//vehicle type
public:
	Vehicle(int n = 0, int n1 = 0, char*s1 = "NULL", char*s2 = "NULL");//constructor
	Vehicle(Vehicle&);//set the vehicle
	int get_Num();// get the car number
	int get_Choice();//get the choice
	std::string get_Lic();// get the license of the car
	std::string get_Type();// get the type of the car
	void browse_Veh();//browse the information
	void modify_Veh(Vehicle&);//modify
	void add_Veh(); //add the people
};
#endif