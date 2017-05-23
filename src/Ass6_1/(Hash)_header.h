#pragma once
//header file: the class of the data structure: Hashtable.

#ifndef HASH_TABLE
#define HASH_TABLE

//header files:
#include "(Node_Declaration).h"

//definition:
#define BUCKETS 8

//class:
class Hash_Driver;
class Hash_Vechile;

class Hash
{
public:
	friend class File_Operation;

public:
	//Hashtable establishment and fixing:
	unsigned long Hash_Key_Name(const char *name);
	virtual unsigned long Hash_Key(void) { return 1024; };

	//add and amend:
	virtual void Hash_Expand() {};
	virtual void Hash_Delete() {};
	virtual void Hash_Amend() {};

	virtual void Hash_Reset() {};

	//Hashtable free:
	virtual void Hash_Free() {};
	//a pure virtual function.

	//Hashtable actions:
	virtual void Hash_Print() {};	//pure virtual function.
	virtual void Hash_Print_Avaliable() {};

protected:
	int hash_size;
};

//derived-class:
class Hash_Driver : public Hash
{
public:
	//constructor:
	Hash_Driver();
	//destructor:
	~Hash_Driver();

public:
	unsigned long Hash_Key(Driver &obj_driver);

	void Hash_Expand(Driver &obj_driver);
	void Hash_Delete(Driver &obj_driver);
	void Hash_Amend(Driver &obj_origin, Driver &obj_new);
	void Hash_Reset();

	void Hash_Free();
	void Hash_Print();
	void Hash_Print_Avaliable();

	driver_node* Get_Node(const char *name);

protected:
	//the main body of the hash table:
	driver_node** table_body;

public:
	//friend class declaration:
	friend class Driver_File;
	friend class systemController;

public:
	void Hash_Print_Corresponding();
};

class Hash_Vehicle : public Hash
{
public:
	//constructor:
	Hash_Vehicle();
	//destructor:
	~Hash_Vehicle();

public:
	unsigned long Hash_Key(Vehicle &obj_vehicle);

	void Hash_Expand(Vehicle &obj_vehicle);
	void Hash_Delete(Vehicle &obj_vehicle);
	void Hash_Amend(Vehicle &obj_origin, Vehicle &obj_new);
	void Hash_Reset();

	void Hash_Free();
	void Hash_Print();
	void Hash_Print_Avaliable();

	vehicle_node* Get_Node(const char *name);

protected:
	//the main body of the hash table:
	vehicle_node** table_body;

public:
	//friend class declaration:
	friend class Vehicle_File;
	friend class systemController;

};

#endif