#include "systemController.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <regex>
	systemController::systemController() {
		/*the constructor:*/
		//section.1: (file establishment)

		//section.2: (hashtable establishment)
		this->driverList->File_To_Hashtable();
		this->vehicleList->File_To_Hashtable();

		//section.3: (LINKAGE establishment)
		this->Link_Set_Up();
	}

	bool systemController::searchKey(char* keys) {
		if (vehicleList->Find(keys) != NULL) {
			Vehicle *veh = vehicleList->Find(keys);
			veh->browse_Veh();
			std::system("PAUSE");
			return true;
		}
		else if (driverList->Find(keys)) {
			Driver *dri = driverList->Find(keys);
			dri->browse_Driver(); // print out single one;
			std::system("PAUSE"); // display and pause here;
			return true;
		}
		else {
			return false;
		}
	}

	bool systemController::addDriver() {
		user_info *newDriverInfo = new user_info;
		char name[20], teleNum[20], gender;
		memset(name, '\0', 20);
		std::cout << "Your Name: " << '\n';
		std::cin.getline(name, 20);
		int countN = 0;
		do
		{
			memset(teleNum, '\0', 20);
			if (countN++ != 0)
			{
				std::cout << "Your Telephone Number: (only numbers and 11 digts)" << '\n';
				std::cin.getline(teleNum, 20);
			}
			else
			{
				std::cout << "Your Telephone Number:" << '\n';
				std::cin.getline(teleNum, 20);
			}
		} while (!this->isTelephone(teleNum));
		do {
			std::cout << "Gender: (m/f)" << '\n';
			
			gender = getch();
		} while (gender != 'm' && gender != 'f');

		if (gender == 'f')
		{
			newDriverInfo->Driver_Sex = 1;
		}
		else if (gender == 'm' )
		{
			newDriverInfo->Driver_Sex = 0;
		}		
		system("PAUSE");
		
		strcpy(newDriverInfo->Driver_Name, name);

		strcpy(newDriverInfo->Driver_Tel, teleNum);
		std::cout << newDriverInfo->Driver_Sex << '\n';
		system("PAUSE");
		driverList->addNew(newDriverInfo);
		//^^^ add the structure to the list;
		//refrash the list;
		
		/* === Add successfully new driver; === */
		if (vehicleList->File_To_Hashtable())
		{
			this->vehicleListAvaliable();
			//^^^ show list of vehicles waiting for choosing one anh link em up;

			char chooseCarInfo[30];
			//std::string chooseCarInfo;
			
			do
			{
				memset(chooseCarInfo, '\0', 30);
				std::cout << "Please enter the plate license of car you want link: (\"jump\" to skip)" << '\n';
				std::cin >> chooseCarInfo;
				//std::cin.getline(chooseCarInfo, 30);
				Vehicle *oldVehicle = vehicleList->Find(chooseCarInfo);

				if (oldVehicle != NULL)
				{
					strcpy(newDriverInfo->Driver_link.license_plate, oldVehicle->Get_info()->Vehicle_link[0].license_plate);
				}
				else if (!strcmp(chooseCarInfo, "jump"))
				{
					break;
				}
				else
				{
					std::cout << "Sorry the object is NOT found" << '\n';
				}
			} while (true);
			this->Link_Set_Up();
			this->noteHistory("Add a new Driver.");
			std::cout << "Object established!" << '\n';
			this->driverListAll();
		}
		

		return true;

	}
	
	bool systemController::addVehicle() {
		car_info *newVehicleInfo = new car_info;
		char *licPlate[15], *type[20];
		std::cout << "license Plate: " << '\n';
		std::cin >> *licPlate;
		strcpy(newVehicleInfo->Vehicle_link[0].license_plate, *licPlate);
		strcpy(newVehicleInfo->Vehicle_link[1].license_plate, *licPlate);

		std::cout << "Type of Vehicle" << '\n';
		std::cin >> *type;
		strcpy(newVehicleInfo->vehicle_type, *type);
		vehicleList->addNew(newVehicleInfo);
		//added a new vehicle;
		this->Link_Set_Up();
		//refrash the list;
		this->driverListAvaliable();
		//display all the avaliable items
		char *chooseDriverInfo;
		std::cout << "Please enter the plate license of car you want link: " << '\n';
		std::cin >> chooseDriverInfo;
		Driver *theDriver = driverList->Find(chooseDriverInfo);

		strcpy(newVehicleInfo->Vehicle_link->driver_Num, theDriver->Get_info()->Driver_link.driver_Num);

		return true;
	}

	void systemController::vehicleListAll() {
		vehicleList->hash_table_V.Hash_Print();
		std::system("PAUSE");
	}

	void systemController::driverListAll() {
		driverList->hash_table_D.Hash_Print();
		std::system("PAUSE");
	}

	void systemController::vehicleListAvaliable() {
		vehicleList->hash_table_V.Hash_Print();
		std::system("PAUSE");
	}

	void systemController::driverListAvaliable() {
		driverList->hash_table_D.Hash_Print();
		std::system("PAUSE");
	}

	bool systemController::modifyDriver() {
		// Find the people
		char* indexDriverNumber;
		int operation;
		std::cout << "Plase located (using Number)at Who: " << '\n';
		std::cin >> indexDriverNumber;

		Driver *oldPointerDriver = driverList->Find(indexDriverNumber);
		Driver oldObjectDriver(oldPointerDriver->Get_info());

		if (oldPointerDriver == NULL) {
			std::cout << "!!!Object NOT found!!!" << '\n';
			return false;
		}
		else
		{
			bool loop1 = 1;
			do
			{
				std::cout << "which item you'd like to modify?" << '\n';
				std::cout << "1 -> Name." << '\n';
				std::cout << "2 -> Gender." << '\n';
				std::cout << "3 -> Telephone number." << '\n';
				std::cout << "4 -> Vehicle attached." << '\n';
				std::cin >> operation;
				
				char *newInfo;
				if (operation==1)
				{
					user_info *newStructDriver = new user_info;
					std::cout << "Please type in the corrected Name: " << '\n';
					std::cin >> newInfo;
					newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					strcpy(newStructDriver->Driver_Name, newInfo);
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					break;
				}
				else if (operation ==2)
				{
					user_info *newStructDriver = new user_info;
					bool newInfoGender, loop2 = 1;
					std::cout << "Please type in the corrected Gender:(M / F) " << '\n';
					std::cin >> newInfo;
					do
					{
						if (*newInfo == 'm' || *newInfo == 'M')
						{
							newInfoGender = 1;
							loop2 = 0;
						}
						else if (*newInfo == 'f' || *newInfo == 'F')
						{
							newInfoGender = 0;
							loop2 = 0;
						}
						else
						{
							std::cout << "Please used the correct format:" << '\n';
							std::cout << "F/f for Female" << '\n' << "M/m for Male" << '\n';
						}
					} while (loop2);
					newStructDriver = oldObjectDriver.Get_info();
					newStructDriver->Driver_Sex = newInfoGender;
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					break;
				}
				else if(operation ==3)
				{
					user_info *newStructDriver = new user_info;
					std::cout << "Please type in the corrected Telephone Number: " << '\n';
					std::cin >> newInfo;
					newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					strcpy(newStructDriver->Driver_Tel, newInfo);
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					break;
				}
				else if (operation == 4)
				{
					user_info *newStructDriver = new user_info;
					std::cout << "Please type in the Vehicle license plate you want to connect: " << '\n';
					std::cin >> newInfo;
					newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					strcpy(newStructDriver->Driver_link.license_plate, newInfo); // change the lcense plate of the link
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					break;
				}
				else
				{
					std::wcout << "Please Enter the correct number option!" << '\n';
					system("PAUSE");
				}

			} while (loop1);

			return true;
		}

	}

	bool systemController::modifyVehicle() {
		char* indexVehicleLP;
		int operation;
		std::cout << "Plase located the Vehicle(using License plate): " << '\n';
		std::cin >> indexVehicleLP;

		Vehicle *oldPointerVehicle = vehicleList->Find(indexVehicleLP);
		Vehicle oldObjectVehicle(oldPointerVehicle->Get_info());

		if (oldPointerVehicle == NULL) {
			std::cout << "!!!Object NOT found!!!" << '\n';
			return false;
		}
		else
		{
			bool loop1 = 1;
			do
			{
				std::cout << "which item you'd like to modify?" << '\n';
				std::cout << "1 -> Vehicle Type." << '\n';
				std::cout << "2 -> Driver of the car." << '\n';
				//std::cout << "3 -> Telephone number." << '\n';
				//std::cout << "4 -> Vehicle attached." << '\n';
				std::cin >> operation;
				car_info *newStructVehicle = new car_info;
				char *newInfo;

				if (operation == 1)
				{
					std::cout << "Please type in the corrected Type: " << '\n';
					std::cin >> newInfo;
					newStructVehicle = oldObjectVehicle.Get_info(); // operation overloading.
					strcpy(newStructVehicle->vehicle_type, newInfo);
					Vehicle newObjectVehicle(newStructVehicle);
					vehicleList->Modify(oldObjectVehicle, newObjectVehicle);
					this->Link_Set_Up();
					loop1 = 0;
					std::cout << "Modified successfully!" << '\n';
				}
				else if (operation == 2)
				{
					bool loop2 = 1;
					do
					{
						std::cout << "Please type in the Driver Number you want to connect: " << '\n';
						std::cin >> newInfo;
						if (driverList->Find(newInfo))
						{
							loop2 = 0;
						}
					} while (loop2);

					newStructVehicle = oldObjectVehicle.Get_info(); // operation overloading.
					strcpy(newStructVehicle->Vehicle_link[0].driver_Num, newInfo); // change the lcense plate of the link
					Vehicle newObjectVehicle(newStructVehicle);
					vehicleList->Modify(oldObjectVehicle, newObjectVehicle);
					this->Link_Set_Up();
					loop1 = 0;
					break;
				}
				else
				{
					std::wcout << "Please Enter the correct number option!" << '\n';
					system("PAUSE");
				}

			} while (loop1);

			return true;
		}

	}

	
	bool systemController::driverDelete() {
		char* indexWho;
		while (true) {
			std::cout << "Please located (using DriverNumber): " << '\n';
			std::cin >> indexWho;
			if (driverList->Find(indexWho)) {
				// Find the object
				Driver *pointerDriver = driverList->Find(indexWho);
				Driver objectDriver(pointerDriver->Get_info());
				driverList->Delete(objectDriver);// Wating for wang
				return true;
			}
			else {
				std::cout << "!!!Object NOT found!!!" << '\n';
				return false;
			}
		}
	}

	bool systemController::vehicleDelete() {
		char* indexWhich;
		while (true) {
			std::cout << "Please located the vehicle(using license plate): " << '\n';
			std::cin >> indexWhich;
			if (driverList->Find(indexWhich)) { 
				// Find the object
				Vehicle *pointerVehicle = vehicleList->Find(indexWhich);
				Vehicle objectVehicle(pointerVehicle->Get_info());
				vehicleList->Delete(objectVehicle);// Wating for wang
				return true;
			}
			else {
				std::cout << "---Object NOT found---" << '\n';
				return false;
			}
		}
	}
	void systemController::DeleteAllVehicle()
	{
		vehicleList->delete_all();
	}
	void systemController::DeleteAllDriver()
	{
		driverList->delete_all();
	}
	/*
	void systemController::DeleteAllVehicle() {
		vehicleList->;
		std::cout << "Delete successful!" << '\n';
	}

	void systemController::DeleteAllDriver() {
		driverList->;
		std::cout << "Delete successful!" << '\n';
	}*/


	// show the historyNote
	void systemController::showEditingRecords() {
		std::ifstream historyNote("editing_history.txt", std::ios::in);
		if (historyNote.is_open()) {
			std::string line;
			while (std::getline(historyNote, line)) {
				std::cout << line << '\n';
			}
			historyNote.close();
		}
		else {
			std::cerr << "Unable to open file\n";
		}
	}

	void systemController::noteHistory(std::string info) {
		std::ofstream historyNote("editing_history.txt", std::ios::out);
		if (historyNote.is_open()) {
			historyNote << info << std::endl;
			historyNote.close();
		}
	}

	bool systemController::isTelephone(char * tele)
	{
		std::string teleStr = tele;
		bool temp = false;
		std::regex e("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");
		if (std::regex_match(tele, e))
		{
			temp = true;
		}
		else {
			temp = false;
		}
		return temp;
	}
	
	void systemController::deleteHistory() {
		std::ofstream historyNote("editing_history.txt", std::ios::trunc);
		if(!historyNote){
		std::cout << "Create file failure...\n";
		}
		historyNote.close();
	}

	void systemController::changeSudoPassword(char *psw) {
		std::ofstream clearFile("password.txt", std::ios::trunc);
		std::ofstream passWord("password.txt", std::ios::out);
		if (passWord.is_open()) {
			passWord << psw << std::endl;
			passWord.close();
		}
	}

	/*char *systemController::getUserPassword() {
		char password[30];
		std::ifstream getPassword("password.txt", std::ios::in);
		if (getPassword.is_open()) {
			try {
				std::getline(getPassword, password); // set password to the first line of the file.
			}
			catch(){ // excepetion
				*password = NULL;
			}
			getPassword.close();
			return password; // maybe wrong...
		}
		else {
			std::cerr << "Get password error..." << '\n';
			return NULL;
		}

	}
	*/

	systemController::~systemController() {
		delete driverList;
		delete vehicleList;
	}

	void systemController::Link_Set_Up() {
		/*as the initialization of the "DATA STRUCTURE"!*/
		driver_node *head_d = new driver_node;
		for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
			head_d = driverList->hash_table_D.table_body[i];
			while ((head_d->next) != NULL) {
				head_d = head_d->next;	//move to the last node.
				if (strcmp(head_d->_driver.Get_info()->Driver_link.license_plate, "No_Vehicle") != 0 &&
					head_d->_driver.Get_info()->Driver_link.license_plate != NULL &&
					strlen(head_d->_driver.Get_info()->Driver_link.license_plate) != 0)
				{
					if (head_d->_driver.Get_info()->Driver_link.license_plate == NULL) {
						std::cout << "2333333" << '\n';
					}
					//this person has a car:
					vehicle_node *head_v = new vehicle_node;
					head_v = vehicleList->hash_table_V.Get_Node(head_d->_driver.Get_info()->Driver_link.license_plate);

					/*The Linkage Between Driver & Vehicle!!*/
					//link: driver -> vehicle:
					head_d->_his_car = head_v;
					//link: vehicle -> driver:	(specially: 2 pilots means 2 nodes)
					if (head_v->_its_pilot[0] == NULL)
						head_v->_its_pilot[0] = head_d;
					else if (head_v->_its_pilot[1] == NULL)
						head_v->_its_pilot[1] = head_d;
				}
			}	//show the principle of the hashtable
		}
	}
	
  void systemController::punishment(){
    //system("cls");
    
    std::cout << "The punishment is shown as below\n";
    std::cout << "---------------------------------------------------------------------------------------\n";
    std::cout << "1.Driving_the_bus_overloading_more_than_20\n";
    std::cout << "2.Over_speeding\n";
    std::cout << "3.Deliberately_block_the_number_plate\n";
    std::cout << "4.Deliberately_stop_in_the_expressway_lane\n";
    std::cout << "5.Continuous_driving_medium_sized_passenger_car_dangerous_goods_transport_\n"
      "vehicles_more_than_4_hours_without_stopping_or_parking_rest_time_less_than_20_minutes\n";
    std::cout << "6.Driving_school_bus_without_getting_the_specific_license\n";
    std::cout << "7.Drunk_driving\n";
    std::cout << "8.Escape_after_a_traffic_accident\n";
    std::cout << "---------------------------------------------------------------------------------------\n";
    std::cout << "Which punishment do you want to choose to add to this driver? (No.1-8)\n";
    int num;
    std::cin >> num;
    dr->punishment_Driver(num);
    //dr->
  }

  void systemController::reward(){
    //system("cls");

    std::cout << "The reward is shown as below\n";
    std::cout << "---------------------------------------------------------------------------------------\n";
    std::cout << "1.Take_care_of_the_overall_situation_the_interests_of_the_company_as_a_matter_of_dedication\n";
    std::cout << "2.vehicles_parked_after_safe_and_safekeeping_measures\n";
    std::cout << "3.minutes_before_the_arrival_of_the_guests_to_the_guard\n";
    std::cout << "4.Arrangements_for_easy_driving_routes_not_out_of_time_for_private_affairs\n";
    std::cout << "5.Continue_to_enhance_business_learning_self_improvement\n";
    std::cout << "6.Good_braking_effect\n";
    std::cout << "7.No_maintenance_shop_to_ask_for_any_property_of_the_phenomenon\n";
    std::cout << "8.Vehicles_on_request_self_study_self_repair\n";
    std::cout << "---------------------------------------------------------------------------------------\n";
    std::cout << "Which reward do you want to choose to add to this driver? (No.1-8)\n";
    int num;
    std::cin >> num;
    dr->reward_Driver(num);
    //dr->
  }
  /*void systemController::show_money(){
    std::cout << dr->get_money();
  }*/