#include "driver.h"
#include <iostream>
using namespace std;
/*	std::string Driver_Name; //driver name
	std::string Driver_Sex; // drvier sex
	std::string Driver_Tel;//driver's telephone
	std::string Driver_Usingtime;//using time
	std::string Driver_Returntime;//return time
	int Veh_num;*/
//set the driver
Driver::Driver(Driver&Driver){
	Driver_Name = Driver.get_Name();
	Driver_Sex = Driver.get_Sex();
	Driver_Tel = Driver.get_Tel();
	Driver_Usingtime = Driver.get_Usingtime();
	Driver_Returntime = Driver.get_Returntime();
}
// get the people name
string Driver:: get_Name(){
	return Driver_Name;
}
// get the license of the car
string Driver:: get_Sex(){
	return Driver_Sex;
}
// get the type of the car
string Driver::get_Tel(){
	return Driver_Tel;
}
//get the using time of the car
string Driver:: get_Usingtime(){
	return Driver_Usingtime;
}
//get the return time of the car
string Driver:: get_Returntime(){
	return Driver_Returntime;
}
//browse
void Driver:: browse_Driver(){
}
//modify
void Driver:: modify_Driver(){
}
//rewards
void Driver:: rewards_Driver(){
}
//payment
void Driver:: payment_Driver(){
}
//delete
void Driver::delete_Driver(){
}