#pragma once
//header file: the class represents for the data base. All operations revolved around the file is included in this class.

#ifndef FILE_OPERATION
#define FILE_OPERATION

//header file:
#include <fstream>
#include "(Hash)_header.h"

//base class:
class File_Operation
{
public:
	//functional self-defined functions:
	virtual bool File_To_Hashtable() = 0;	//create the hashtable at the very beginning.
	virtual void Hashtable_To_File() {};

public:
	virtual void addNew(void) {};
	virtual void modify(void) {};
	virtual void delete_all(void) {};
};

//derived-class:
class Driver_File : public File_Operation
{
public:
	//constructor:
	Driver_File();

public:
	bool File_To_Hashtable();
	void Hashtable_To_File();

public:
	//add:
	void addNew(user_info *struct_new);

	//modify:
	Driver* Find(char *dn);
	void Modify(Driver &obj_origin, Driver &obj_new);
	void Delete(Driver &obj_origin);

	//delete:
	void delete_all();

protected:
//public:
	Hash_Driver hash_table_D;

public:
	//friend class declaration:
	friend class systemController;
};

class Vehicle_File : public File_Operation
{
public:
	//constructor:
	Vehicle_File();

public:
	bool File_To_Hashtable();
	void Hashtable_To_File();

public:
	//add (vehicle):
	void addNew(car_info *struct_new);	//a new ID should be created.

										//modify (vehicle):
	Vehicle* Find(char *lp);
	void Modify(Vehicle &obj_origin, Vehicle &obj_new);
	void Delete(Vehicle &obj_origin);

	//delete:
	void delete_all();

protected:
	Hash_Vehicle hash_table_V;

public:
	//friend class declaration:
	friend class systemController;
};

#endif