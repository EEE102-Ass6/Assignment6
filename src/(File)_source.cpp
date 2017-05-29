//source file: the class represents for the data base. All operations revolved around the file is included in this class.

using namespace std;

//header files:
#include <iostream>
#include "(File)_header.h"

/*--------------------Driver:--------------------*/

//constructor:
Driver_File::Driver_File() {
	//if the file does not exist, create one:
	ofstream file_create(file_name_d, ios::app | ios::binary);
	file_create.close();

	ifstream file_check;	//read only:
	file_check.open(file_name_d, ios::in | ios::binary);
	if (file_check.fail()) {
		cout << "Error! Cannot open the file..." << endl; Sleep(2000);
		file_check.close();
		std::exit(0);
	}
	else {
		//cout << "The file: '" << file_name_d << "' is found." << endl;
		file_check.close();
		//std::system("PAUSE");
	}
}

//functional:
void Driver_File::File_Arrange() {
	int file_position = 0;
	FILE *ptr_temp, *ptr_driver;
	ptr_temp = fopen("temp.dat", "wb");
	ptr_driver = fopen(file_name_d, "rb");
	if (ptr_driver == NULL || ptr_temp == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		user_info *temp = new user_info;
		while (fread(temp, sizeof(user_info), 1, ptr_driver)) {
			file_position++;
			temp->position_in_file = file_position;
			fwrite(temp, sizeof(user_info), 1, ptr_temp);
		}
		sizeof_driver_file = 0;
	}
	fclose(ptr_temp);
	fclose(ptr_driver);
	remove(file_name_d);				//delete the origin file
	DeleteFile(TEXT(file_name_d));		//delete the origin file (confirm, delete again.)
	rename("temp.dat", file_name_d);	//change name into origin file

										//recreate the hash table:
	this->hash_table_D.Hash_Reset();
	this->File_To_Hashtable();
}
bool Driver_File::File_To_Hashtable() {
	user_info *user_temp = new user_info;
	ifstream acc_hash_d;
	//read only
	acc_hash_d.open(file_name_d, ios::in | ios::binary);
	if (acc_hash_d.fail()) {
		//cout << "Error! Cannot open the file..." << endl; Sleep(2000);
		acc_hash_d.close();
		return false;
		//std::exit(0);
	}
	else {
		//cout << "Hashtable is creating..." << endl;
		for (int i = 0; !acc_hash_d.eof(); i++) {
			if (!acc_hash_d.read((char*)user_temp, sizeof(user_info)))
				break;	//this time, read failed...
			else {
				/*----------Expanding----------*/
				//create an object:
				Driver driver_temp(user_temp);
				//send object into the hash table:
				this->hash_table_D.Hash_Expand(driver_temp);
				//position:
				sizeof_driver_file++;
				/*-----------------------------*/
			}
		}
		acc_hash_d.close();
		//cout << "Hashtable inspection complete!" << endl;
		return true;
	}
}
void Driver_File::Hashtable_To_File() {
	//
}

//add:
void Driver_File::addNew(user_info *struct_new) {
	//size amend:
	sizeof_driver_file++;
	struct_new->position_in_file = sizeof_driver_file;

	cout << sizeof_driver_file << endl;
	std::system("PAUSE");

	Driver obj_new(struct_new);
	//add to the hashtable (add node, form linkage):
	this->hash_table_D.Hash_Expand(obj_new);

	//add to the file:
	/*------------file operation: write in the file.------------*/
	//input process. automatically generates file:
	ofstream acc_save(file_name_d, ios::app | ios::binary);
	acc_save.write((char*)struct_new, sizeof(user_info));
	acc_save.close();
	/*----------------------------------------------------------*/
}

//modify:
Driver* Driver_File::Find(char *dn) {
	if (hash_table_D.Get_Node(dn) != NULL)
		return &hash_table_D.Get_Node(dn)->_driver;
	else
		return NULL;
}

void Driver_File::Modify(Driver *obj_origin, Driver &obj_new) {
	/*change both in hashtable & file:*/

	//amend in hashtable:
	this->hash_table_D.Hash_Amend(obj_origin, obj_new);	//the position in file should not be changed!!

	/*--------------------amend in file:--------------------*/

	FILE *ptr_driver;
	if ((ptr_driver = fopen(file_name_d, "rb+")) == NULL) {	//'r+': read and amend file information
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);	/*Test the success of opening the file*/
	}
	else {
		fseek(ptr_driver, (obj_new.Get_info()->position_in_file - 1) * sizeof(user_info), SEEK_SET);
		fwrite(obj_new.Get_info(), sizeof(user_info), 1, ptr_driver);
		fclose(ptr_driver);
		ptr_driver = NULL;
	}

	/*------------------------------------------------------*/
}

void Driver_File::Delete(Driver *obj_origin) {
	/*change both in hashtable & file:*/

	//amend in hashtable:
	this->hash_table_D.Hash_Delete(obj_origin);

	/*--------------------delete in file:--------------------*/

	//delete info in driver database:
	FILE *ptr_temp, *ptr_driver;
	ptr_temp = fopen("temp.dat", "wb");
	ptr_driver = fopen(file_name_d, "rb");
	if (ptr_driver == NULL || ptr_temp == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		user_info temp;
		while (fread(&temp, sizeof(user_info), 1, ptr_driver)) {
			if (strcmp(temp.Driver_link.driver_Num, obj_origin->Get_info()->Driver_link.driver_Num) != 0)
				fwrite(&temp, sizeof(user_info), 1, ptr_temp);
			fflush(stdin);
		}
	}
	fclose(ptr_driver);
	fclose(ptr_temp);
	remove(file_name_d);				//delete the origin file
	DeleteFile(TEXT(file_name_d));		//delete the origin file (confirm, delete again.)
	rename("temp.dat", file_name_d);	//change name into origin file

										/*------------------------------------------------------*/

}

void Driver_File::delete_all() {
	//delete hash table:
	hash_table_D.Hash_Free();
	hash_table_D.Hash_Reset();

	//delete original file:
	remove(file_name_d);				//delete the origin file
	DeleteFile(TEXT(file_name_d));		//delete the origin file (confirm, delete again.)

										//create new one:
	ofstream file_create(file_name_d, ios::app | ios::binary);
	file_create.close();

	//number of file size:
	sizeof_driver_file = 0;
}

/*-----------------------------------------------*/

/*-------------------Vehicle:--------------------*/

//constructor:
Vehicle_File::Vehicle_File() {
	//if the file does not exist, create one:
	ofstream file_create(file_name_v, ios::app | ios::binary);
	file_create.close();

	ifstream file_check;	//read only:
	file_check.open(file_name_v, ios::in | ios::binary);
	if (file_check.fail()) {
		cout << "Error! Cannot open the file..." << endl; Sleep(2000);
		file_check.close();
		std::exit(0);
	}
	else {
		//cout << "The file: '" << file_name_v << "' is found." << endl;
		file_check.close();
		//std::system("PAUSE");
	}
}

//functional:
void Vehicle_File::File_Arrange() {
	int file_position = 0;
	FILE *ptr_temp, *ptr_car;
	ptr_temp = fopen("temp.dat", "wb");
	ptr_car = fopen(file_name_v, "rb");
	if (ptr_car == NULL || ptr_temp == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		car_info temp;
		while (fread(&temp, sizeof(car_info), 1, ptr_car)) {
			file_position++;
			temp.position_in_file = file_position;
			fwrite(&temp, sizeof(car_info), 1, ptr_temp);
		}
		sizeof_vehicle_file = 0;
	}
	fclose(ptr_temp);
	fclose(ptr_car);
	remove(file_name_v);				//delete the origin file
	DeleteFile(TEXT(file_name_v));		//delete the origin file (confirm, delete again.)
	rename("temp.dat", file_name_v);	//change name into origin file
										//recreate the hash table:
	this->hash_table_V.Hash_Reset();
	this->File_To_Hashtable();
}
bool Vehicle_File::File_To_Hashtable() {
	car_info *car_temp = new car_info;
	ifstream acc_hash_v;
	//read only
	acc_hash_v.open(file_name_v, ios::in | ios::binary);
	if (acc_hash_v.fail()) {
		cout << "Error! Cannot open the file..." << endl; Sleep(2000);
		acc_hash_v.close();
		return false;
		//		std::exit(0);
	}
	else {
		//cout << "Hashtable is creating..." << endl;
		for (int i = 0; !acc_hash_v.eof(); i++) {
			if (!acc_hash_v.read((char*)car_temp, sizeof(car_info)))
				break;	//this time, read failed...
			else {
				/*----------Expanding----------*/
				//create an object:
				Vehicle vehicle_temp(car_temp);	//a struct: 'car_info' is passed in.
												//send object into the hash table:
				this->hash_table_V.Hash_Expand(vehicle_temp);
				//position:
				sizeof_vehicle_file++;
				/*-----------------------------*/
			}
		}
		acc_hash_v.close();
		//cout << "Hashtable inspection complete!" << endl;
		return true;
	}
}
void Vehicle_File::Hashtable_To_File() {
	//
}

//add:
void Vehicle_File::addNew(car_info *struct_new) {
	//size amend:
	sizeof_vehicle_file++;
	struct_new->position_in_file = sizeof_vehicle_file;

	Vehicle obj_new(struct_new);

	//add to the hashtable (add node, form linkage):
	this->hash_table_V.Hash_Expand(obj_new);

	//add to the file:
	/*------------file operation: write in the file.------------*/
	//input process. automatically generates file:
	ofstream acc_save(file_name_v, ios::app | ios::binary);
	acc_save.write((char*)struct_new, sizeof(car_info));
	acc_save.close();
	/*----------------------------------------------------------*/
}

//modify:
Vehicle* Vehicle_File::Find(char *lp) {
	if (hash_table_V.Get_Node(lp) != NULL)
		return &hash_table_V.Get_Node(lp)->_vehicle;
	else
		return NULL;
}

void Vehicle_File::Modify(Vehicle *obj_origin, Vehicle &obj_new) {
	/*change both in hashtable & file:*/

	//amend in hashtable:
	this->hash_table_V.Hash_Amend(obj_origin, obj_new);

	/*--------------------amend in file:--------------------*/

	FILE *ptr_account;
	if ((ptr_account = fopen(file_name_v, "rb+")) == NULL) {	//'r+': read and amend file information
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);	/*Test the success of opening the file*/
	}
	else {
		fseek(ptr_account, (obj_new.Get_info()->position_in_file - 1) * sizeof(car_info), SEEK_SET);
		fwrite(obj_new.Get_info(), sizeof(car_info), 1, ptr_account);
		fclose(ptr_account);
		ptr_account = NULL;
	}

	/*------------------------------------------------------*/
}

void Vehicle_File::Delete(Vehicle *obj_origin) {
	/*change both in hashtable & file:*/

	//amend in hashtable:
	this->hash_table_V.Hash_Delete(obj_origin);

	/*--------------------delete in file:--------------------*/

	//delete info in vehicle database:
	FILE *ptr_temp, *ptr_vehicle;
	ptr_temp = fopen("temp.dat", "wb");
	ptr_vehicle = fopen(file_name_v, "rb");
	if (ptr_vehicle == NULL || ptr_temp == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		car_info temp;
		while (fread(&temp, sizeof(car_info), 1, ptr_vehicle)) {
			if (strcmp(temp.Vehicle_link[0].license_plate, obj_origin->Get_info()->Vehicle_link[0].license_plate) != 0 &&
				strcmp(temp.Vehicle_link[1].license_plate, obj_origin->Get_info()->Vehicle_link[1].license_plate) != 0) {
				fwrite(&temp, sizeof(car_info), 1, ptr_temp);
				cout << temp.vehicle_type << endl;
			}
			fflush(stdin);
		}
	}
	fclose(ptr_vehicle);
	fclose(ptr_temp);
	remove(file_name_v);				//delete the origin file
	DeleteFile(TEXT(file_name_v));		//delete the origin file (confirm, delete again.)
	rename("temp.dat", file_name_v);	//change name into origin file

	cout << "vehicle delete function is called." << endl;
										/*------------------------------------------------------*/
}

void Vehicle_File::delete_all() {
	//delete hash table:
	hash_table_V.Hash_Free();
	hash_table_V.Hash_Reset();

	//delete original file:
	remove(file_name_v);				//delete the origin file
	DeleteFile(TEXT(file_name_v));		//delete the origin file (confirm, delete again.)

										//create new one:
	ofstream file_create(file_name_v, ios::app | ios::binary);
	file_create.close();

	//number of file size:
	sizeof_vehicle_file = 0;
}

void Vehicle_File::getobj_to_modify() {

}
/*-----------------------------------------------*/

//change the name of the file:
/*
File_Operation::File_Operation() {
//ask for the "file's name" from the user:
cout << "Please input the name of file: " << endl;
static string name_temp;

//receive (with robustness test):
cin.sync();
getline(cin, name_temp);

//name assign:
static char *name = const_cast<char*>(name_temp.c_str());
file_name = name;

//file create:
this->File_Operation_Constructor();
}
*/