/*drivers
book information

function
1.modify
2.rewards
3.punishment
4.delete
*/
#ifndef _DRIVER
#define _DRIVER
#include <iostream>
class Driver{
private:
	std::string Driver_Name; //driver name
	std::string Driver_Sex; // drvier sex
	std::string Driver_Tel;//driver's telephone
	std::string Driver_Usingtime;//using time
	std::string Driver_Returntime;//return time
	int Veh_num;//vehicle
public:
	Driver(char*s1 = "NULL", char*s2 = "NULL",
		char*s3 = "NULL", char*s4 = "NULL", char*s5 = "NULL", int n = 0);//constructor
	Driver(Driver&);//set the driver
	std::string get_Name();// get the people name
	std::string get_Sex();// get the license of the car
	std::string get_Tel();// get the type of the car
	std::string get_Usingtime();//get the using time of the car
	std::string get_Returntime();//get the return time of the car
	void browse_Driver();//browse
	void modify_Driver();//modify
	void rewards_Driver();//rewards
	void payment_Driver();//payment
	void delete_Driver();//delete
};
#endif