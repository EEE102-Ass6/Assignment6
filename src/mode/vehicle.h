/*drivers
book information

function
1.modify
2.rewards
3.punishment
4.delete
*/
#ifndef _VEHICLE
#define _VEHICLE
class Vehicle{
private:
  int num; //car number
  int people_num;//people number
  char  license_plate[10];//license plate
  char  vehicle_type[10];//vehicle type

public:
  Vehicle(int n = 0, int n1 = 0, char*s1 = "NULL", char*s2 = "NULL");//constructor
  void set_Veh(int n, int n1, char*s1, char*s2);//set the vehicle
  int get_Num();// get the car number
  char *get_Lic();// get the license of the car
  char *get_Type();// get the type of the car
  void modify();//modify
  void add(); //add the people
  

};
#endif