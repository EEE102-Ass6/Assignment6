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

struct User{
  char Driver_Name[20]; //driver name
  bool Driver_Sex; // drvier sex
  char Driver_Tel[20];//driver's telephone
  //int Veh_num;//vehicle
};

struct link{
  int driver_Num;
  int vehicle_Num;
};

class Driver{
private:
  User user;
public:
  /*Driver(char*s1 = "NULL", char*s2 = "NULL",
    char*s3 = "NULL", char*s4 = "NULL", char*s5 = "NULL", int n = 0);//constructor
  Driver(Driver&);//set the driver
  std::string get_Name();// get the people name
  std::string get_Sex();// get the license of the car
  std::string get_Tel();// get the type of the car
  std::string get_Usingtime();//get the using time of the car
  std::string get_Returntime();//get the return time of the car*/
 // User get();
  void set_User(User * user);
  void browse_Driver();//browse
  void modify_Driver();//modify
  void rewards_Driver();//rewards
  void payment_Driver();//payment
  void delete_Driver();//delete
};
#endif