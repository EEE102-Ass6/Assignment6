#pragma once

#ifndef _DRIVER
#define _DRIVER

//header files:
#include "(Linkage)_header.h"
typedef enum PUNISHMENT // define the enum type of month from jannuary to decemeber
{
  Driving_the_bus_overloading_more_than_20 = 100,
  Over_speeding = 200,
  Deliberately_block_the_number_plate = 300,
  Deliberately_stop_in_the_expressway_lane = 400,
  Continuous_driving_medium_sized_passenger_car_dangerous_goods_transport_vehicles_more_than_4_hours_without_stopping_or_parking_rest_time_less_than_20_minutes = 500,
  Driving_school_bus_without_getting_the_specific_license = 600,
  Drunk_driving = 700,
  Escape_after_a_traffic_accident = 800,
};
typedef enum REWARD // define the enum type of month from jannuary to decemeber
{
  Take_care_of_the_overall_situation_the_interests_of_the_company_as_a_matter_of_dedication = 100,
  vehicles_parked_after_safe_and_safekeeping_measures = 200,
  minutes_before_the_arrival_of_the_guests_to_the_guard = 300,
  Arrangements_for_easy_driving_routes_not_out_of_time_for_private_affairs = 400,
  Continue_to_enhance_business_learning_self_improvement = 500,
  Good_braking_effect = 600,
  No_maintenance_shop_to_ask_for_any_property_of_the_phenomenon = 700,
  Vehicles_on_request_self_study_self_repair = 800,
};
struct user_info {
  char Driver_Name[20];// =  NULL ;	// driver name
  char Driver_Tel[20];// = { NULL };	// driver's telephone
	bool Driver_Sex;		// drvier sex
							//the position in file:
	int position_in_file;
  int money=1000;//Driver's money
	//the linkage:
	link Driver_link;
};	//what we read from the file.

	//class:
class Driver {
public:
	//constructor:
	Driver();
	Driver(user_info *temp);

public:
  
	void set_User(user_info *target);
	void Car_Delete(char *license_plate);

	void browse_Driver();	//browse
	void modify_Driver();	//modify
	void rewards_Driver();	//rewards
	void payment_Driver();	//payment
	void delete_Driver();	//delete
  void punishment_Driver(int num);
  void reward_Driver(int num);
	void set_vehicle(int carNumber);
  int get_money();

public:
	user_info* Get_info() { return &this->user; };

private:
	user_info user;
};

#endif