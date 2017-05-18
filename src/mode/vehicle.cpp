#include"vehicle.h"
#include <iostream>
#include <string>
using namespace std;

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

//browse the information
void Vehicle::browse_Veh(){
	system("cls");
	cout << "The vehicle information is shown as below" << endl;
	cout << num << endl;
	cout << license_plate << endl;
	cout << vehicle_type << endl;
}

//modify
void Vehicle::modify_Veh(Vehicle&Vehicle){
	//cout << "Do you want to"
	system("cls");
	cout << "********modify vehicle***********" << endl;
	cout << "please input the vehicle number" << endl;
	int n;
	cin >> n;
	//for (int k = 0; k < 100; k++){//for multiple vehicles
		if (n == Vehicle.get_Num()){
			Vehicle.browse_Veh();
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
						   num = n1;
						   break;
				}
				case 2:{
						   cout << "please input vehicle license:" << endl;
						   string s1;
						   cin >> s1;
						   license_plate = s1;
						   break;
				}
				case 3:{
						   cout << "please input vehicle Type:" << endl;
						   string s2;
						   cin >> s2;
						   vehicle_type = s2;
						   break;
				}
				default:
					break;
				}
			}
		}
	

}

//add the people
void Vehicle::add_Veh(){
	system("cls");
	cout << "********add vehicle's information" << endl;
	int n;
	string s1, s2;
	cout << "please input vehicle number:" << endl;
	cin >> n;
	num = n;
	cout << "please input vehicle license:" << endl;
	cin >> s1;
	license_plate = s1;
	cout << "please input vehicle Type:" << endl;
	cin >> s2;
	vehicle_type = s2;
	cout << "successful add!!!" << endl;

}
