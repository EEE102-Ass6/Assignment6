#include"vehicle.h"
#include <iostream>
#include <string>
using namespace std;

/*
Vehicle::Vehicle(Vehicle& Vehicle){
  num = Vehicle.get_Num();
  license_plate = Vehicle.get_Lic();
  vehicle_type = Vehicle.get_Type();
}
// get the car number
int Vehicle::get_Num()
{
  return num;
}
// get the choice
int Vehicle::get_Choice()
{
  system("cls");
  cout << "***********************" << endl;
  cout << "********Vehicle********" << endl;
  cout << "1. browse vehicles' information" << endl;
  cout << "2. modify vehicles" << endl;
  cout << "3. add vehicles" << endl;
  cout << "***********************" << endl;
  int n;
  cin >> n;
  while (n<1 || n>3){
    cout << "error input, please input again" << endl;
    cin >> n;
  }
  return n;
}
// get the license of the car
string Vehicle::get_Lic(){
  return license_plate;
}

// get the type of the car
string Vehicle::get_Type(){
  return vehicle_type;
}
*/
//browse the information
void Vehicle::browse_Veh(car_info *vehicle){
  system("cls");
  cout << "The vehicle information is shown as below" << endl;
  cout << vehicle->num << endl;
  cout << vehicle->license_plate << endl;
  cout << vehicle->vehicle_type << endl;
}


void Vehicle::Set_Veh(car_info* target){
  strcpy(vehicle.num, target->num);
  strcpy(vehicle.license_plate, target->license_plate);
  strcpy(vehicle.vehicle_type, target->vehicle_type);
}

//modify
void Vehicle::modify_Veh(Vehicle&Vehicle,car_info*target){
  //cout << "Do you want to"
  system("cls");
  cout << "********modify vehicle***********" << endl;
  cout << "please input the vehicle number" << endl;
  int n;
  cin >> n;
  for (int k = 0; k < 100; k++){//for multiple vehicles
    if (n == vehicle.num[k]){
      Vehicle.browse_Veh(target);
      cout << "Are you sure to change the vehicle's information Y|N" << endl;
      char x;
      cin >> x;
      if (x == 'Y' || x == 'y'){
        cout << "which one do you want to change" << endl;
        cout << "1. vehicle number" << endl;
        cout << "2. vehicle license" << endl;
        cout << "3. vehicle type" << endl;
        int n;
        cin >> n;
        while (n<1 || n>3){
          cout << "error input!!! please input again" << endl;
          cin >> n;
        }
        switch (n)
        {
        case 1:{
                 cout << "please input vehicle number:" << endl;
                 int n1;
                 cin >> n1;
                 target->num[k] = n1;
                 Vehicle.Set_Veh(target);
                 break;
        }
        case 2:{
                 cout << "please input vehicle license:" << endl;
                 char s1;
                 cin >> s1;
                 target->license_plate[k] = s1;
                 Vehicle.Set_Veh(target);
                 break;
        }
        case 3:{
                 cout << "please input vehicle Type:" << endl;
                 char s2;
                 cin >> s2;
                 target->vehicle_type[k] = s2;
                 Vehicle.Set_Veh(target);
                 break;
        }
        default:
          break;
        }
      }
    }
  }

}

//add the people
void Vehicle::add_Veh(car_info*target){
  system("cls");
  cout << "********add vehicle's information" << endl;
  int n;
  char s1, s2;
  cout << "please input vehicle number:" << endl;
  cin >> n;
  target->num[n] = n;
  cout << "please input vehicle license:" << endl;
  cin >> s1;
  target->license_plate[n] = s1;
  cout << "please input vehicle Type:" << endl;
  cin >> s2;
  target->vehicle_type[n] = s2;
  cout << "successful add!!!" << endl;

}
