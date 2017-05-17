/*drivers
book information

function
1.modify
2.rewards
3.punishment
4.delete
*/
#ifndef  _DRIVER
#define _DRIVER
class Driver{
private:
  char Driver_Name[10]; //driver name
  char Driver_Sex[10]; // drvier sex
  char Driver_Tel[15];//driver's telephone
  char Driver_Usingtime[20];//using time
  char Driver_Returntime[20];//return time
  int Veh_num;//vehicle
public:
  Driver(char*s1 = "NULL", char*s2 = "NULL",
             char*s3 = "NULL", char*s4 = "NULL", char*s5 = "NULL", int n = 0);//constructor
  void   Driver(char*s1, char*s2,
    char*s3, char*s4, char*s5, int n);//set the driver
  char *get_Name();// get the people name
  char *get_Sex();// get the license of the car
  char *get_Tel();// get the type of the car
  char *get_Usingtime();//get the using time of the car
  char *get_Returntime();//get the return time of the car
  void modify();//modify
  void rewards();//rewards
  void payment();//payment
  void dele();//delete

};
#endif