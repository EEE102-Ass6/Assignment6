//source file: the class of the data structure: Hashtable (detailed description).

using namespace std;

//header file:
#include <iostream>
#include "(Hash)_header.h"

/*------------------------------Hash (base class): ------------------------------*/

//selfdefined functions (functional):
unsigned long Hash::Hash_Key_Name(const char *name) {
	//return value: "the hash key"
	int result = 0;
	unsigned long nHash = 0;

	while (*name)
		nHash = (nHash << 5) + nHash + *name++;

	result = nHash % BUCKETS;
	return result;
}

/*-------------------------------------------------------------------------------*/

/*-------------------------Hash_Driver (derived-class): -------------------------*/

//constructor & destructor:
Hash_Driver::Hash_Driver() {
	hash_size = 0;
	table_body = (driver_node**)malloc(BUCKETS * sizeof(driver_node*));
	for (int i = 0; i < BUCKETS; i++) {
		table_body[i] = (driver_node*)malloc(sizeof(driver_node));
		table_body[i]->next = NULL;
	}	//memory allocation process for hashtable
	//cout << "empty Hashtable is established (drivers)!" << endl;
}
Hash_Driver::~Hash_Driver() {
	//the destructor is called successfully.
}

unsigned long Hash_Driver::Hash_Key(Driver &obj_driver) {
	int key = (int)Hash_Key_Name(obj_driver.Get_info()->Driver_link.driver_Num);
	return key;
}

void Hash_Driver::Hash_Expand(Driver &obj_driver) {
	//hash key calculation:
	int key = (int)Hash_Key(obj_driver);

	driver_node *head;
	head = table_body[key];

	while (head->next != NULL)
		head = head->next;	//move to the last node.

	//memory allocation: create a new node.
	head->next = (driver_node*)malloc(sizeof(driver_node));
	head = head->next;
	head->next = NULL;

	//value assigning (add):
	head->_driver = obj_driver;
	head->_his_car = NULL;

	//total size increased.
	(this->hash_size)++;
}

void Hash_Driver::Hash_Delete(Driver *obj_driver) {
	//hash key calculation:
	int key = (int)Hash_Key(*obj_driver);

	driver_node *head = new driver_node;
	head = table_body[key];

	driver_node *temp = new driver_node;

	while (head->next != NULL) {
		//making comparison:
		if (!strcmp(head->next->_driver.Get_info()->Driver_link.driver_Num,
			obj_driver->Get_info()->Driver_link.driver_Num)) {	//the correct node is found!
																//corresponding operations:
			if (head->next->_his_car != NULL) {
				/*it means he has a car.*/
				//delete this car's pilot:
				head->next->_his_car->_vehicle.Pilot_Delete(head->next->_driver.Get_info()->Driver_link.driver_Num);

				//amend in file:
				FILE *ptr_account;
				if ((ptr_account = fopen(file_name_v, "rb+")) == NULL) {	//'r+': read and amend file information
					printf("There was a problem opening the file, please restart the program.\n\n");
					Sleep(3000); exit(0);	/*Test the success of opening the file*/
				}
				else {
					fseek(ptr_account, (head->next->_his_car->_vehicle.Get_info()->position_in_file - 1) * sizeof(car_info), SEEK_SET);
					fwrite(head->next->_his_car->_vehicle.Get_info(), sizeof(car_info), 1, ptr_account);
					fclose(ptr_account);
					ptr_account = NULL;
				}

				//delete the linkage between nodes.
				for (int i = 0; i < 2; i++) {
					if (head->next->_his_car->_its_pilot[i] == head->next)
						head->next->_his_car->_its_pilot[i] = NULL;
				}
			}
			//node in this linked list:
			temp = head->next;
			head->next = head->next->next;
			break;
		}
		else
			head = head->next;
	}
	std::free(temp);

	//total size increased.
	(this->hash_size)--;
}

void Hash_Driver::Hash_Amend(Driver *obj_origin, Driver &obj_new) {
	/*making change in the hashtable.*/
	this->Hash_Delete(obj_origin);
	this->Hash_Expand(obj_new);
}

void Hash_Driver::Hash_Reset(void) {
	hash_size = 0;
	table_body = (driver_node**)malloc(BUCKETS * sizeof(driver_node*));
	for (int i = 0; i < BUCKETS; i++) {
		table_body[i] = (driver_node*)malloc(sizeof(driver_node));
		table_body[i]->next = NULL;
	}	//memory allocation process for hashtable
	//cout << "empty Hashtable is established (drivers)!" << endl;
}

//fetch functions:
driver_node* Hash_Driver::Get_Node(const char *name) {
	//calculate the hash key:
	int key = (int)Hash_Key_Name(name);
	driver_node *head;
	head = this->table_body[key];
	while (head->next != NULL) {
		head = head->next;
		if (!strcmp(head->_driver.Get_info()->Driver_link.driver_Num, name)) {
			//the node is found!
			return head;
		}
	}
	//the node is not found...
	return NULL;
}

//Hashtable free:
void Hash_Driver::Hash_Free(void) {
	driver_node *head, *move, *store;
	for (int i = 0; i < BUCKETS; i++) {
		head = table_body[i];
		move = head;
		while ((move->next) != NULL) {
			store = move->next;
			std::free(move);
			move = store;
		}
	}
	std::free(table_body);
}

//Actions:
void Hash_Driver::Hash_Print(void) {
	driver_node *head;
	//printf("Hashtable size: %d.\n", hash_size);
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		//printf("%d. bucket No.%d\n", i, i + 1);
		while ((head->next) != NULL) {
			head = head->next;	//move to the last node.
			head->_driver.browse_Driver();
		}	//show the principle of the hashtable
	}
	//the announcement:
	//printf("Reading hashtable success!\n");
	//std::system("PAUSE");
}

void Hash_Driver::Hash_Print_Avaliable(void) {
	driver_node *head;
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		while ((head->next) != NULL) {
			head = head->next;	//move to the next node.
			if (head->_driver.Get_info()->Driver_link.license_plate == NULL ||
				!strcmp(head->_driver.Get_info()->Driver_link.license_plate, "No_Vehicle") ||
				strlen(head->_driver.Get_info()->Driver_link.license_plate) == 0) {
				//drivers without car.
				head->_driver.browse_Driver();
			}
		}	//show the principle of the hashtable
	}
	std::system("PAUSE");
}

void Hash_Driver::Hash_Print_Corresponding(void) {
	driver_node *head;
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		while ((head->next) != NULL) {
			head = head->next;	//move to the next node.
			if (head->_his_car != NULL) {
				//he has a car!
				head->_driver.browse_Driver();
				head->_his_car->_vehicle.browse_Veh();
			}
		}	//show the principle of the hashtable
	}
	//std::system("PAUSE");
}

/*-------------------------------------------------------------------------------*/

/*-------------------------Hash_Vechile (derived-class): ------------------------*/

//constructor & destructor:
Hash_Vehicle::Hash_Vehicle() {
	hash_size = 0;
	table_body = (vehicle_node**)malloc(BUCKETS * sizeof(vehicle_node*));

	for (int i = 0; i < BUCKETS; i++) {
		table_body[i] = (vehicle_node*)malloc(sizeof(vehicle_node));
		table_body[i]->next = NULL;
	}	//memory allocation process for hashtable
	//cout << "empty Hashtable is established (vechiles)!" << endl;
}
Hash_Vehicle::~Hash_Vehicle() {
	//the destructor is called successfully.
}

unsigned long Hash_Vehicle::Hash_Key(Vehicle &obj_vehicle) {
	//hash key calculation:
	int key = (int)Hash_Key_Name(obj_vehicle.Get_info()->Vehicle_link[0].license_plate);
	return key;
}

void Hash_Vehicle::Hash_Expand(Vehicle &obj_vehicle) {
	//hash key calculation:
	int key = (int)Hash_Key(obj_vehicle);

	vehicle_node *head = new vehicle_node;
	head = table_body[key];
	//move to the last node.
	while (head->next != NULL)
		head = head->next;
	//memory allocation: create a new node.
	head->next = (vehicle_node*)malloc(sizeof(vehicle_node));
	head = head->next;
	head->next = NULL;

	//value assigning (add new node):
	head->_vehicle = obj_vehicle;
	for (int i = 0; i < 2; i++)
		head->_its_pilot[i] = NULL;

	//total size increased.
	(this->hash_size)++;
}

void Hash_Vehicle::Hash_Delete(Vehicle *obj_vehicle) {
	//hash key calculation:
	int key = (int)Hash_Key(*obj_vehicle);

	vehicle_node *head = new vehicle_node;
	head = table_body[key];

	vehicle_node *temp = new vehicle_node;

	while (head->next != NULL) {
		//making comparison:
		if (!strcmp(head->next->_vehicle.Get_info()->Vehicle_link[0].license_plate, obj_vehicle->Get_info()->Vehicle_link[0].license_plate) ||
			!strcmp(head->next->_vehicle.Get_info()->Vehicle_link[1].license_plate, obj_vehicle->Get_info()->Vehicle_link[1].license_plate)) {
			//corresponding operations:
			for (int i = 0; i < 2; i++) {
				if (head->next->_its_pilot[i] != NULL) {
					/*it means this car belons to someone (that person!).*/
					//delete this pilot's car:
					head->next->_its_pilot[i]->_driver.Car_Delete(head->next->_vehicle.Get_info()->Vehicle_link[i].license_plate);

					//amend in file:
					FILE *ptr_account;
					if ((ptr_account = fopen(file_name_d, "rb+")) == NULL) {	//'rb+': read and amend file information
						printf("There was a problem opening the file, please restart the program.\n\n");
						Sleep(3000); exit(0);	/*Test the success of opening the file*/
					}
					else {
						fseek(ptr_account, (head->next->_its_pilot[i]->_driver.Get_info()->position_in_file - 1) * sizeof(user_info), SEEK_SET);
						fwrite(head->next->_its_pilot[i]->_driver.Get_info(), sizeof(user_info), 1, ptr_account);
						fclose(ptr_account);
						ptr_account = NULL;
					}

					//delete the linkage between nodes.
					head->next->_its_pilot[i]->_his_car = NULL;
				}
			}
			temp = head->next;
			head->next = head->next->next;
			break;
		}
		else
			head = head->next;
	}
	std::free(temp);

	//total size increased.
	(this->hash_size)--;
}

void Hash_Vehicle::Hash_Amend(Vehicle *obj_origin, Vehicle &obj_new) {
	/*making change in the hashtable.*/
	this->Hash_Delete(obj_origin);
	this->Hash_Expand(obj_new);
}

void Hash_Vehicle::Hash_Reset(void) {
	hash_size = 0;
	table_body = (vehicle_node**)malloc(BUCKETS * sizeof(vehicle_node*));
	for (int i = 0; i < BUCKETS; i++) {
		table_body[i] = (vehicle_node*)malloc(sizeof(vehicle_node));
		table_body[i]->next = NULL;
	}	//memory allocation process for hashtable
	//cout << "empty Hashtable is established (vechiles)!" << endl;
}

//fetch functions:
vehicle_node* Hash_Vehicle::Get_Node(const char *name) {
	//calculate the hash key:
	int key = (int)Hash_Key_Name(name);
	vehicle_node *head;
	head = this->table_body[key];
	while (head->next != NULL) {
		head = head->next;
		if (!strcmp(head->_vehicle.Get_info()->Vehicle_link[0].license_plate, name) ||
			!strcmp(head->_vehicle.Get_info()->Vehicle_link[1].license_plate, name)) {	//2 links.
																						//the node is found!
			return head;
		}
	}
	//the node is not found...
	return NULL;
}

//Hashtable free:
void Hash_Vehicle::Hash_Free(void) {
	vehicle_node *head, *move, *store;
	for (int i = 0; i < BUCKETS; i++) {
		head = table_body[i];
		move = head;
		while ((move->next) != NULL) {
			store = move->next;
			std::free(move);
			move = store;
		}
	}
	std::free(table_body);
}

//Actions:
void Hash_Vehicle::Hash_Print(void) {
	vehicle_node *head;
	//printf("Hashtable size: %d.\n", hash_size);
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		//printf("%d. bucket No.%d\n", i, i + 1);
		while ((head->next) != NULL) {
			head = head->next;
			//content show:
			head->_vehicle.browse_Veh();
		}	//show the principle of the hashtable
	}
	//the announcement:
	//printf("Reading hashtable success!\n");
	//std::system("PAUSE");
}

void Hash_Vehicle::Hash_Print_Avaliable(void) {
	vehicle_node *head;
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		while ((head->next) != NULL) {
			head = head->next;	//move to the next node.
			if (head->_vehicle.Get_info()->Vehicle_link[0].driver_Num == NULL ||
				!strcmp(head->_vehicle.Get_info()->Vehicle_link[0].driver_Num, "No_Pilot") ||
				strlen(head->_vehicle.Get_info()->Vehicle_link[0].driver_Num) == 0 ||
				head->_vehicle.Get_info()->Vehicle_link[1].driver_Num == NULL ||
				!strcmp(head->_vehicle.Get_info()->Vehicle_link[1].driver_Num, "No_Pilot") ||
				strlen(head->_vehicle.Get_info()->Vehicle_link[1].driver_Num) == 0) {
				//drivers without car.
				head->_vehicle.browse_Veh();
			}
		}	//show the principle of the hashtable
	}
	std::system("PAUSE");
}

/*-------------------------------------------------------------------------------*/