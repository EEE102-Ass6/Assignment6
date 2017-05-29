#include "systemController.h"

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
		//initialization:
		memset(newDriverInfo->Driver_link.driver_Num, '\0', 15);
		memset(newDriverInfo->Driver_link.license_plate, '\0', 15);
		strcpy(newDriverInfo->Driver_link.license_plate, "No_Vehicle");

		char name[20], teleNum[20], gender, sortNumb[15];
		memset(name, '\0', 20);

		std::cout << "Name: " << '\n';
		std::cin >> name;
		int countN = 0;
		do {
			memset(teleNum, '\0', 20);
			if (countN++ != 0) {
				std::cout << "Telephone Number: (only numbers and 11 digts)" << '\n';
				std::cin >> teleNum;
			}
			else {
				std::cout << "Telephone Number:" << '\n';
				std::cin >> teleNum;
			}
		} while (!this->isTelephone(teleNum));

		do {
			std::cout << "Gender: (m/f)" << '\n';
			gender = getch();
			std::cout << gender << '\n';
		} while (gender != 'm' && gender != 'f');

		if (gender == 'f') {
			newDriverInfo->Driver_Sex = 0;
		}
		else if (gender == 'm' ) {
			newDriverInfo->Driver_Sex = 1;
		}

		strcpy(newDriverInfo->Driver_Name, name);
		strcpy(newDriverInfo->Driver_Tel, teleNum);

		memset(sortNumb, '\0', 15);
		ltoa(this->the_Last_Number(), sortNumb, 10);
		strcpy(newDriverInfo->Driver_link.driver_Num, sortNumb);

		driverList->addNew(newDriverInfo);
		this->Link_Set_Up();

		std::string info = "Add a new Driver";
		this->noteHistory(info);
		std::cout << "Object established!" << '\n';
		this->driverListAll();
		return true;
	}
	
	bool systemController::addVehicle() {
		car_info *newVehicleInfo = new car_info;
		for (int i = 0; i < 2; i++) {
			memset(newVehicleInfo->Vehicle_link[i].driver_Num, '/0', 15);
		}
		for (int i = 0; i < 2; i++) {
			strcpy(newVehicleInfo->Vehicle_link[i].driver_Num, "No_Pilot");
		}

		char licPlate[15], type[20];
		memset(licPlate, '/0', 15);
		memset(type, '/0', 20);
		std::cout << "License Plate: " << '\n';
		std::cin >> licPlate;

		if (this->hasVehicle(licPlate)) {
			std::cout << "Sorry the license plate has already exist!" << std::endl;
			std::cout << "Please check out the list or the License plate again." << std::endl;
			system("PAUSE");
			return false;
		}
		for (int i = 0; i < 2; i++) {
			strcpy(newVehicleInfo->Vehicle_link[i].license_plate, licPlate);
		}
		memset(licPlate, '/0', 15);

		std::cout << "Type of Vehicle:" << '\n';
		std::cin >> type;
		strcpy(newVehicleInfo->vehicle_type, type);
		memset(type, '/0', 20);
		
		vehicleList->addNew(newVehicleInfo);
		this->Link_Set_Up();
		
		std::string info = "Add a new Vehicle";
		this->noteHistory(info);
		std::cout << "Vehicle Object established!" << '\n';
		this->vehicleListAll();
		return true;
	}

	void systemController::vehicleListAll() {
		vehicleList->hash_table_V.Hash_Print();
	}

	void systemController::driverListAll() {
		driverList->hash_table_D.Hash_Print();
	}

	void systemController::vehicleListAvaliable() {
		vehicleList->hash_table_V.Hash_Print();
	}

	void systemController::driverListAvaliable() {
		driverList->hash_table_D.Hash_Print();
	}

	bool systemController::modifyDriver() {
		// Find the people
		if (this->driverList->hash_table_D.hash_size == 0) {
			std::cout<<"Your List is empty!"<<std::endl;
			std::system("PAUSE");
			return false;
		}

		char indexDriverNumber[15];
		int operation;
		std::cout << "Plase located (using Number)at Who: " << '\n';
		std::cin >> indexDriverNumber;

		Driver *oldPointerDriver = driverList->Find(indexDriverNumber);
		
		if (oldPointerDriver == NULL) {
			std::cout << "!!!Object NOT found!!!" << '\n';
			return false;
		}
		else {
			Driver oldObjectDriver(oldPointerDriver->Get_info());
			bool loop1 = 1;
			do {
				std::cout << "which item you'd like to modify?" << '\n';
				std::cout << "1 -> Name." << '\n';
				std::cout << "2 -> Gender." << '\n';
				std::cout << "3 -> Telephone number." << '\n';
				std::cout << "4 -> Vehicle attached." << '\n';
				std::cin >> operation;
				
				if (operation == 1) {
					char newInfo[20];
					memset(newInfo, '\0', 20);
					user_info *newStructDriver = new user_info;
					std::cout << "Please type in the corrected Name: " << '\n';
					std::cin >> newInfo;
					newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					strcpy(newStructDriver->Driver_Name, newInfo);
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(&oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					std::string info = newObjectDriver.Get_info()->Driver_Name;
					this->noteHistory("Modify driver Name to: " + info );
					break;
				}
				else if (operation == 2) {
					char newInfo[20];
					memset(newInfo, '\0', 20);
					user_info *newStructDriver = new user_info;
					bool newInfoGender, loop2 = 1;
					std::cout << "Please type in the corrected Gender:(m/f) " << '\n';
					std::cin >> newInfo;
					do {
						if (*newInfo == 'm' || *newInfo == 'M') {
							newInfoGender = 1;
							loop2 = 0;
						}
						else if (*newInfo == 'f' || *newInfo == 'F') {
							newInfoGender = 0;
							loop2 = 0;
						}
						else {
							std::cout << "Please used the correct format:" << '\n';
							std::cout << "f for Female" << '\n' << "m for Male" << '\n';
						}
					} while (loop2);
					newStructDriver = oldObjectDriver.Get_info();
					newStructDriver->Driver_Sex = newInfoGender;
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(&oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					std::string gender;
					if (newObjectDriver.Get_info()->Driver_Sex == false) {
						gender = "female";
					} else if (newObjectDriver.Get_info()->Driver_Sex == true) {
						gender = "male";
					}
					std::string info = gender;
					this->noteHistory("Modify driver gender to: " + info);
					break;
				}
				else if (operation == 3) {
					char newInfo[20];
					user_info *newStructDriver = new user_info;
					int countN = 0;
					do {
						memset(newInfo, '\0', 20);
						
						if (countN++ != 0) {
							std::cout << "Telephone Number: (only numbers and 11 digts)" << '\n';
							std::cin >> newInfo;
						}
						else {
							std::cout << "Please type in the corrected Telephone Number: " << '\n';
							std::cin >> newInfo;
						}
					} while (!this->isTelephone(newInfo));
					newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					strcpy(newStructDriver->Driver_Tel, newInfo);
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(&oldObjectDriver, newObjectDriver);
					this->Link_Set_Up();
					loop1 = 0;
					std::string info = newObjectDriver.Get_info()->Driver_Tel;
					this->noteHistory("Modify driver telephone to: " + info);
					break;
				}
				else if (operation == 4) {
					// change the connect vehicle:
					if (this->vehicleList->hash_table_V.hash_size == 0) {
						std::cout << "The vehicle list is empty, please add vehicle FIRST!!!" << std::endl;
						loop1 = 0; break;
					}
					char newInfo[20];
					//user_info *newStructDriver = new user_info;
					int countN = 0;
					bool loopLocal = 1;
					Vehicle *findObjVehicle;
					do {
						memset(newInfo, '\0', 20);
						// times various display different info:
						if (countN != 0) {
							this->vehicleListAvaliable();
							std::cout << "youcan use 'q'to quit the connect part." << std::endl;
							std::cout << "Please type in the Vehicle license plate you want to connect:('release' to unlock the driver and vehicle)" << std::endl;
							std::cin >> newInfo;
							findObjVehicle = vehicleList->Find(newInfo);
						}
						else {
							this->vehicleListAvaliable();
							std::cout << "Please type in the Vehicle license plate you want to connect:('release' to unlock the driver and vehicle)" << std::endl;
							std::cin >> newInfo;
							findObjVehicle = vehicleList->Find(newInfo);
						}

						// judge the list 
						if (findObjVehicle != NULL) {
							if (!findObjVehicle->canAddDriver())
							{
								std::cout << " Sorry the object is not Avaliable!" << std::endl;
								system("PAUSE");
								//this->vehicleListAvaliable();
								std::cout << "Please check the Vehicle license plate in the list below to connect." << std::endl;
							}
							else
							{
								loopLocal = 0;
							}	
							//std::cout << " You can try again" << std::endl;
						}
						else if (!strcmp(newInfo,"release")) {
							loopLocal = 0;
						}
						else if (!strcmp(newInfo, "q")) {
							loopLocal = 0;
						}
						else {
							std::cout << " Sorry the object is not found" << std::endl;
							system("PAUSE");
							std::cout << "Please check the Vehicle license plate in the list below to connect." << std::endl;
						}
						countN++;
					} while (loopLocal);

					user_info *newStructDriver = oldObjectDriver.Get_info(); // operation overloading.
					
					if (!strcmp(newInfo,"release")) 	{
						memset(newInfo, '\0', 20);
						strcpy(newInfo,"No_Vehicle");
					}else if (!strcmp(newInfo, "q")) {
						std::cout << "Quit the adding part successfully !" << std::endl;
						loop1 = 0;
						break;// break the if;
					}

					strcpy(newStructDriver->Driver_link.license_plate, newInfo); // change the license plate of the link
					Driver newObjectDriver(newStructDriver);
					driverList->Modify(&oldObjectDriver, newObjectDriver);
					this->User_Link(newObjectDriver);
					this->everything_Reset();
					this->Link_Set_Up();
					loop1 = 0;
					std::string info = newObjectDriver.Get_info()->Driver_link.license_plate;
					this->noteHistory("Modify driver vehicle:" + info );
					std::cout << "Modify successfully!" << std::endl;
				}
				else {
					std::wcout << "Please Enter the correct number option!" << std::endl;
					system("PAUSE");
				}
				
			} while (loop1);
			
			return true;
		}
	}

	bool systemController::modifyVehicle() {

		if (this->vehicleList->hash_table_V.hash_size == 0) {
			std::cout << "Your List is empty!" << std::endl;
			std::system("PAUSE");
			return false;
		}

		char indexVehicleLP[15];
		memset(indexVehicleLP, '\0', 15);
		int operation;
		std::cout << "Plase located the Vehicle(using License plate): " << '\n';
		std::cin >> indexVehicleLP;

		Vehicle *oldPointerVehicle = vehicleList->Find(indexVehicleLP); // find the object pointer;
		//Vehicle oldObjectVehicle(oldPointerVehicle->Get_info());		// create a object;

		if (oldPointerVehicle == NULL) {
			std::cout << "!!!Object NOT found!!!" << '\n';
			return false;
		}
		else {
			bool loop1 = 1;
			do {
				car_info *newStructVehicle = new car_info;
				//initialization:
				for (int i = 0; i < 2; i++) {
					memset(newStructVehicle->Vehicle_link[i].driver_Num, '\0', 15);
					memset(newStructVehicle->Vehicle_link[i].license_plate, '\0', 15);
				}
				memset(newStructVehicle->vehicle_type, '\0', 15);
				Driver *getPointerDriA;
				std::string newInfo;
				std::cout << "which item you'd like to modify?" << '\n';
				std::cout << "1 -> Vehicle Type." << '\n';
				std::cout << "2 -> Driver of the car." << '\n';
				std::cin >> operation;
				
				if (operation == 1) {
					std::cout << "Please type in the corrected Type: " << '\n';
					std::cin >> newInfo;
					newStructVehicle = oldPointerVehicle->Get_info(); // operation overloading.
					char newInfoChar[15];
					memset(newInfoChar, '/0', 15);
					strcpy(newInfoChar, newInfo.c_str());
					strcpy(newStructVehicle->vehicle_type, newInfoChar);
					Vehicle newObjectVehicle(newStructVehicle);
					vehicleList->Modify(oldPointerVehicle, newObjectVehicle);
					this->Car_Link(newObjectVehicle);	//2017.5.28
					this->Link_Set_Up();
					loop1 = 0;
					std::string info = oldPointerVehicle->Get_info()->vehicle_type;
					this->noteHistory("Modify vehicle:" +info);

					std::cout << "Modified successfully!" << std::endl;
				}
				else if (operation == 2) {
					char driIndex[15];
					bool loop2 = true;
					int countN = 0;
					do {
							
							memset(driIndex, '\0', 15);	//initialization.
							if (countN != 0) {
								this->driverListAvaliable();
								
								std::cout << "Please type in the Driver Number you want to connect:('remove' to remove)" << std::endl;
							}
							else {
								this->driverListAvaliable();
								std::cout << "Please type in the Driver Number you want to connect:('remove' to remove) " << std::endl;
							}
							std::cin >> driIndex;
							countN++;
							Driver* getPointerDri = driverList->Find(driIndex);
							if (!strcmp(driIndex, "remove")) {
								//Vehicle *vehObj = ;
								bool lp = 1;
								do {
									std::cout << "1." << oldPointerVehicle->Get_info()->Vehicle_link[0].driver_Num << "\t" << std::endl;
									std::cout << "2." << oldPointerVehicle->Get_info()->Vehicle_link[1].driver_Num << "\t" << std::endl;
									std::cout << "Which driver would you like to remove?" << std::endl;
																	
									char choose = getch();
									std::cout << choose;
									if (choose == '1') {
										//memset(driverList->Find(oldPointerVehicle->Get_info()->Vehicle_link[0].driver_Num)->Get_info()->Driver_link.license_plate, '\0', 15);
										//strcpy(driverList->Find(oldPointerVehicle->Get_info()->Vehicle_link[0].driver_Num)->Get_info()->Driver_link.license_plate, "No_Plate");
										memset(oldPointerVehicle->Get_info()->Vehicle_link[0].driver_Num, '\0', 15);
										strcpy(oldPointerVehicle->Get_info()->Vehicle_link[0].driver_Num, "No_Pilot");
										lp = 0;
									}
									else if (choose == '2') {
										//memset(driverList->Find(oldPointerVehicle->Get_info()->Vehicle_link[1].driver_Num)->Get_info()->Driver_link.license_plate, '\0', 15);
										//strcpy(driverList->Find(oldPointerVehicle->Get_info()->Vehicle_link[1].driver_Num)->Get_info()->Driver_link.license_plate, "No_Plate");
										memset(oldPointerVehicle->Get_info()->Vehicle_link[1].driver_Num, '\0', 15);
										strcpy(oldPointerVehicle->Get_info()->Vehicle_link[1].driver_Num, "No_Pilot");
										lp = 0;
									}
									else {

										std::cout << "Sorry, not correct!\n do again" << std::endl;
										std::system("PAUSE");
									}
								} while (lp);
								loop2 = false;
								Vehicle newObjectVehicle(newStructVehicle);

								vehicleList->Modify(oldPointerVehicle, newObjectVehicle);
								this->Car_Link(newObjectVehicle);
								this->Link_Set_Up();
								loop1 = 0;
								std::string info = newObjectVehicle.Get_info()->Vehicle_link[0].driver_Num;
								std::string info1 = newObjectVehicle.Get_info()->Vehicle_link[1].driver_Num;
								this->noteHistory("Removed one driver of vehicle:\n1." + info + "\n2." + info1);
								std::cout << "Remove successfully!" << std::endl;
								break;
								// remove process: over
							}
							else if (getPointerDri != NULL) {
								if (!getPointerDri->canAddVehicle())
								{
									std::cout << " Sorry the object is not Avaliable!" << std::endl;
									system("PAUSE");
									//this->vehicleListAvaliable();
									std::cout << "Please check the Driver number in the list below to connect." << std::endl;
								}
								else
								{
									getPointerDriA = driverList->Find(driIndex);
									loop2 = 0;
								}
								
							}
							else if (!strcmp(driIndex, "q")) {
								loop2 = 0;
							}
							else {
								std::cout << "The driver is NOT found !!! )" << std::endl;
							}
							
					} while (loop2);
					if (!strcmp(driIndex, "q"))
					{
						std::cout << "Quit the addition part successfully!" << std::endl;
						loop1 == 0;
						break;
					}
					newStructVehicle = oldPointerVehicle->Get_info(); // operation overloading.
					for (int i = 0; i < 2; i++) {
						if (!strcmp(newStructVehicle->Vehicle_link[i].driver_Num,"No_Pilot")) {
							memset(newStructVehicle->Vehicle_link[i].driver_Num, '\0', 15);
							if (strcmp(getPointerDriA->Get_info()->Driver_link.driver_Num,"No_Number") != 0 ) {
								strcpy(newStructVehicle->Vehicle_link[i].driver_Num, getPointerDriA->Get_info()->Driver_link.driver_Num);
							}
							break;
						}
						else {
							//
						}
					}
					
					Vehicle newObjectVehicle(newStructVehicle);

					vehicleList->Modify(oldPointerVehicle, newObjectVehicle);
					this->Car_Link(newObjectVehicle);
					this->everything_Reset();
					this->Link_Set_Up();
					loop1 = 0;
					std::string info = newObjectVehicle.Get_info()->Vehicle_link[0].driver_Num;
					std::string info1 = newObjectVehicle.Get_info()->Vehicle_link[1].driver_Num;
					this->noteHistory("Modify vehicle driver:\n1." + info + "\n2."+ info1);
					std::cout << "Modify successfully!" << std::endl;
					break;

				}
				else {
					std::wcout << "Please Enter the correct number option!" << '\n';
					system("PAUSE");
				}

			} while (loop1);

			return true;
		}
	}

	bool systemController::driverDelete() {
		char indexWho[15]; // Use the Number to get the info:
		memset(indexWho, '/0', 15);
		while (true) {
			std::cout << "Please located (using DriverNumber): " << '\n';
			std::cin >> indexWho;
			if (driverList->Find(indexWho)) {
				// Find the object
				Driver *pointerDriver = new Driver(driverList->Find(indexWho)->Get_info());
				driverList->Delete(pointerDriver);			// Wating for wang
				std::cout << "---Delete successful!---" << std::endl;
				this->everything_Reset();
				this->Link_Set_Up();
				return true;
			}
			else {
				std::cout << "!!!Object NOT found!!!" << '\n';
				return false;
			}
		}
	}

	bool systemController::vehicleDelete() {
		char indexWhich[15];
		memset(indexWhich, '/0', 15);
		while (true) {
			std::cout << "Please located the vehicle(using license plate): " << '\n';
			std::cin >> indexWhich;
			if (vehicleList->Find(indexWhich) != NULL) { 
				// Find the object
				Vehicle *pointerVehicle = new Vehicle(vehicleList->Find(indexWhich)->Get_info());
				vehicleList->Delete(pointerVehicle);			// Wating for wang
				std::cout << "---Delete successful!---" << '\n';
				this->everything_Reset();
				this->Link_Set_Up();
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
		std::cout << "delete all driver successful!" << std::endl;
		this->noteHistory("Delete all vehicle data");
	}

	void systemController::DeleteAllDriver()
	{
		driverList->delete_all();
		std::cout << "delete all driver successful!" << std::endl;
		this->noteHistory("Delete all driver data");
	}
	
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
		std::ofstream historyNote("editing_history.txt", std::ios::app|std::ios::out);
		if (historyNote.is_open()) {
			historyNote << info << "\t" << this->time_ret() << std::endl;
			historyNote.close();
		}
	}

	bool systemController::isTelephone(char * tele)
	{
		std::string teleStr = tele;
		bool temp = false;
		std::regex e("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");
		if (std::regex_match(tele, e)) {
			temp = true;
		}
		else {
			temp = false;
		}
		return temp;
	}
	
	void systemController::deleteHistory() {
		std::ofstream historyNote("editing_history.txt", std::ios::trunc);
		if (!historyNote) {
			std::cout << "Create file failure...\n";
		}
		historyNote.close();
	}

	bool systemController::canAddDriver(Vehicle *oldVehicle, user_info *newDriverInfo)
	{
		car_info *oldVehicleInfo = oldVehicle->Get_info();

		if (strcmp(oldVehicle->Get_info()->Vehicle_link[0].driver_Num, "No_Pilot") == 0) {
			strcpy(oldVehicleInfo->Vehicle_link[0].driver_Num, newDriverInfo->Driver_link.driver_Num);
			Vehicle newVehicle(oldVehicleInfo);
			vehicleList->Modify(oldVehicle, newVehicle);
			
			Vehicle *oldNewVehicle = vehicleList->Find(newVehicle.Get_info()->Vehicle_link[0].license_plate);
			this->Car_Link(*oldNewVehicle);
			this->everything_Reset();
			this->Link_Set_Up();
			return true;
		}else if (strcmp(oldVehicleInfo->Vehicle_link[1].driver_Num, "No_Pilot") == 0) {
			strcpy(oldVehicleInfo->Vehicle_link[1].driver_Num, newDriverInfo->Driver_link.driver_Num);
			Vehicle newVehicle(oldVehicleInfo);
			vehicleList->Modify(oldVehicle, newVehicle);
			Vehicle *oldNewVehicle = vehicleList->Find(newVehicle.Get_info()->Vehicle_link[1].license_plate);
			this->Car_Link(*oldNewVehicle);
			this->everything_Reset();
			this->Link_Set_Up();
			return true;
		}
		else {
			return false;
		}		
	}

	bool systemController::canAddVehicle(Driver *, car_info *)
	{

		return false;
	}

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
				head_d = head_d->next;	//move to the next node.
				if (strcmp(head_d->_driver.Get_info()->Driver_link.license_plate, "No_Vehicle") != 0 &&
					strlen(head_d->_driver.Get_info()->Driver_link.license_plate) != 0) {
					//means: this person has a car:
					vehicle_node *head_v = new vehicle_node;
					head_v = vehicleList->hash_table_V.Get_Node(head_d->_driver.Get_info()->Driver_link.license_plate);
					/*The Linkage Between Driver & Vehicle!!*/
					//link: driver -> vehicle:
					if (head_v != NULL) {
						head_d->_his_car = head_v;
						//link: vehicle -> driver:	(specially: 2 pilots means 2 nodes)
						for (int i = 0; i < 2; i++) {
							if (head_v->_its_pilot[i] == NULL) {
								head_v->_its_pilot[i] = head_d; break;
							}
						}
						if (head_v->_its_pilot[0] != head_d && head_v->_its_pilot[1] != head_d) {
							std::cout << "Warning, program error...(ask wjh for help)" << std::endl;
							std::system("PAUSE"); exit(0);
						}
					}
				}
			}	//show the principle of the hashtable
		}
	}

	void systemController::User_Link(Driver &obj) {
		//find that car, change his pilot.
		if (this->vehicleList->Find(obj.Get_info()->Driver_link.license_plate) != NULL) {
			this->vehicleList->Find(obj.Get_info()->Driver_link.license_plate)->pilot_Change(obj.Get_info()->Driver_link.driver_Num);
			Vehicle newObjectVehicle(vehicleList->Find(obj.Get_info()->Driver_link.license_plate)->Get_info());
			vehicleList->Modify(vehicleList->Find(obj.Get_info()->Driver_link.license_plate), newObjectVehicle);
		}
	}
	
	void systemController::Car_Link(Vehicle &obj) {
		//find that person, change his car.
		for (int i = 0; i < 2; i++) {
			if (this->driverList->Find(obj.Get_info()->Vehicle_link[i].driver_Num) != NULL) {
				this->driverList->Find(obj.Get_info()->Vehicle_link[i].driver_Num)->car_Change(obj.Get_info()->Vehicle_link[i].license_plate);
				Driver newObjectDriver(driverList->Find(obj.Get_info()->Vehicle_link[i].driver_Num)->Get_info());
				driverList->Modify(driverList->Find(obj.Get_info()->Vehicle_link[i].driver_Num), newObjectDriver);
				//break; 2017.5.28 fixed.
			}
		}
	}

	long systemController::the_Last_Number() {
		static char result[sizeof(long)];
		std::ifstream acc_num;
		//read only
		acc_num.open("lastNumber.txt", std::ios::in);
		long number;
		if (acc_num.fail()) {
			//std::cout << "Error! Cannot open the file..." << std::endl; Sleep(2000);
			acc_num.close();
			std::ofstream file_create("lastNumber.txt", std::ios::out);
			if (file_create.is_open()) {
				file_create << this->lastIdNumber;
				file_create.close();
			}
			return 10000;
		}
		else {
			if (acc_num.is_open()) {
				std::string line;
				while (std::getline(acc_num, line));
				number = atol(line.c_str());
				if (this->lastIdNumber <= number)
				{
					this->lastIdNumber = ++number;
					std::ofstream file_create("lastNumber.txt", std::ios::out);
					if (file_create.is_open()) {
						file_create << this->lastIdNumber;
						file_create.close();
					}
				}
				acc_num.close();
			}
			return number;
		}
	}

	void systemController::doRewardsAndPunishiment() {
		char dn[15];
		bool loop2 = true;
		do
		{
			memset(dn, '\0', 15);
			std::cout << "Find your Driver: 'q' to quit editing punishment\n" << std::endl;
			std::cin >> dn;
			if (!strcmp(dn, "q"))
			{
				return;
			}
			else if (driverList->Find(dn) != NULL)
			{
				loop2 = false;
			}
		} while (loop2);
		Driver *objectDriver = new Driver(this->driverList->Find(dn)->Get_info());
		char choose;
		do
		{
			std::cout << "1->Rewards;" <<std::endl;
			std::cout << "2-.Punishment;" << std::endl;
			choose = getch();
			std::cout << choose;
			if (choose == '1')
			{
				this->reward(objectDriver);
				break;
			}
			else if (choose =='2')
			{
				this->punishment(objectDriver);
				break;
			}
		} while (true);
	}

	void systemController::punishment(Driver * objectDriver) {
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
		PUNISHMENT d;
		switch (num)
		{
		case 1: d = Driving_the_bus_overloading_more_than_20; break;
		case 2: d = Over_speeding; break;
		case 3: d = Deliberately_block_the_number_plate; break;
		case 4: d = Deliberately_stop_in_the_expressway_lane; break;
		case 5: d = Continuous_driving_medium_sized_passenger_car_dangerous_goods_transport_vehicles_more_than_4_hours_without_stopping_or_parking_rest_time_less_than_20_minutes;
			break;
		case 6: d = Driving_school_bus_without_getting_the_specific_license; break;
		case 7: d = Drunk_driving; break;
		case 8: d = Escape_after_a_traffic_accident; break;
		default:
			break;
		}
		std::cout << "Punishment is " << d << "гд" << std::endl;
		objectDriver->punishment_Driver(num);

		Driver newObj(objectDriver->Get_info());

		driverList->Modify(driverList->Find(objectDriver->Get_info()->Driver_link.driver_Num), newObj);

		driverList->Find(newObj.Get_info()->Driver_link.driver_Num)->browse_Driver();

		//std::cout << "The totally money is " << driverList->Find(newObj.Get_info()->Driver_link.driver_Num)->Get_info()->money << "гд" << std::endl;
		
	}

	void systemController::reward(Driver * objectDriver) {
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
		REWARD d;
		switch (num)
		{
		case 1: d = Take_care_of_the_overall_situation_the_interests_of_the_company_as_a_matter_of_dedication; break;
		case 2: d = vehicles_parked_after_safe_and_safekeeping_measures; break;
		case 3: d = minutes_before_the_arrival_of_the_guests_to_the_guard; break;
		case 4: d = Arrangements_for_easy_driving_routes_not_out_of_time_for_private_affairs; break;
		case 5: d = Continue_to_enhance_business_learning_self_improvement; break;
		case 6: d = Good_braking_effect; break;
		case 7: d = No_maintenance_shop_to_ask_for_any_property_of_the_phenomenon; break;
		case 8: d = Vehicles_on_request_self_study_self_repair; break;
		default:
			break;
		}
		objectDriver->reward_Driver(num);

		Driver newObj(objectDriver->Get_info());

		driverList->Modify(driverList->Find(objectDriver->Get_info()->Driver_link.driver_Num), newObj);

		driverList->Find(newObj.Get_info()->Driver_link.driver_Num)->browse_Driver();

		//std::cout << "The totally money is " << driverList->Find(newObj.Get_info()->Driver_link.driver_Num)->Get_info()->money << "гд" << std::endl;

	}

	void systemController::payment() {
		char lp[15];
		bool loop2 = true;
		do
		{
			memset(lp, '\0', 15);
			
			std::cout << "Find your vehicle:('q' to quit editing payment) \n";
			std::cin >> lp;
			if (!strcmp(lp, "q"))
			{
				return;
			}
			else if (vehicleList->Find(lp) != NULL)
			{
				loop2 = false;
			}
		} while (loop2);
		Vehicle *objectVehicle = new Vehicle(this->vehicleList->Find(lp)->Get_info());

		int d;
		std::cout << "Please input the kilometers:\n";
		std::cin >> d;

		objectVehicle->payment(d);

		Vehicle newObj(objectVehicle->Get_info());

		vehicleList->Modify(vehicleList->Find(objectVehicle->Get_info()->Vehicle_link[0].license_plate), newObj);
		//this->everything_Reset();
		//std::cout << "the total car distance is: " << vehicleList->Find(newObj.Get_info()->Vehicle_link[0].license_plate)->Get_info()->Distance << std::endl;
		//std::cout << "the total car payment is: " << vehicleList->Find(newObj.Get_info()->Vehicle_link[0].license_plate)->Get_info()->Payment << std::endl;
		//vehicleList->Find(newObj.Get_info()->Vehicle_link[0].license_plate)->browse_Veh();
	}

	std::string systemController::time_ret() {
		char year[5];
		char month[3];
		char day[3];
		char hour[3];
		char min[3];
		char second[3];
		char whole_time[100];
		char*   s = (char*)calloc(100, sizeof(char*));
		time_t timep;
		struct tm *p;
		time(&timep);
		p = localtime(&timep);

		memset(year, '\0', 5);
		memset(month, '\0', 3);
		memset(day, '\0', 3);
		memset(hour, '\0', 3);
		memset(min, '\0', 3);
		memset(second, '\0', 3);
		memset(whole_time, '\0', 100);

		itoa(1900 + p->tm_year, year, 10);
		itoa(1 + p->tm_mon, month, 10);
		itoa(p->tm_mday, day, 10);
		itoa(p->tm_hour, hour, 10);
		itoa(p->tm_min, min, 10);
		itoa(p->tm_sec, second, 10);

		switch (p->tm_wday)
		{
		case 1:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Monday");
		case 2:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Tuesday");
		case 3:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Wednesday");
		case 4:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Thursday");
		case 5:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Friday");
		case 6:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Saturday");
		case 7:
			sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Sunday");
			break;
		}
		strcpy(s, whole_time);
		//cout << s;
		std::string str = s;
		return str;

	}

	void systemController::everything_Reset() {
		//std::cout << "driver file: " << std::endl;
		driverList->File_Arrange();
		//std::cout << "vehicle file: " << std::endl;
		vehicleList->File_Arrange();
	}

	bool systemController::hasVehicle(char * lp) {
		Vehicle *objectVeh = vehicleList->Find(lp);
		if (objectVeh != NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	char* systemController::readPassword(void) {
		std::string temp;
		//read file:
		std::ifstream password;
		password.open(file_name_p, std::ios::in);	//read only.
		if (password.fail()) {
			//std::cout << "Error! Cannot open the file..." << std::endl;
			password.close();
			std::ofstream file_create(file_name_p, std::ios::out);
		
			if (file_create.is_open())
			{
				file_create << "1111";
				file_create.close();
			}
			file_create.close();
		
			return "1111";
		}
		else {
			while (std::getline(password, temp)) {
				//cout << temp;
			}
		}
		const int length = strlen(temp.c_str());

		//close the file:
		password.close();
		char* result = new char[length];
		strcpy(result, temp.c_str());
		return result;
	}

	void systemController::changePassword(char *new_password) {
		//file amend:
		FILE *ptr_password;
		if ((ptr_password = fopen(file_name_p, "w")) == NULL) {
			std::cout << "There was a problem opening the file, please restart the program." << std::endl;
			Sleep(3000); exit(0);
			/*Test the success of opening the file*/
		}
		else {
			fwrite(new_password, strlen(new_password), 1, ptr_password);
		}
		fclose(ptr_password);
	}