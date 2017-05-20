/*vehicle
book information

function
1.modify
2.add
*/

#ifndef _VEHICLE
#define _VEHICLE
struct car_info{
  char num [100]; //car number
  //int people_num;//people number
  char license_plate [100];//license plate
  char vehicle_type [100];//vehicle type
};

struct link{
  int vehicle_num;
  int driver_num;
};

class Vehicle{
private:
  car_info vehicle;
public:
 /* Vehicle(int n = 0, int n1 = 0, char*s1 = "NULL", char*s2 = "NULL");//constructor
  Vehicle(Vehicle&);//set the vehicle
  int get_Num();// get the car number
  int get_Choice();//get the choice
  char* get_Lic();// get the license of the car
  char* get_Type();// get the type of the car*/
  //Vehicle(struct )
  void Set_Veh(car_info *vehicle);
  //car_info Get();
  void browse_Veh(car_info *vehicle);//browse the information
  void modify_Veh(Vehicle&, car_info*vehicle);//modify
  void add_Veh(car_info*vehicle); //add the people
};
#endif