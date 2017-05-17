//header file: the class of the data structure: Hashtable.

#ifndef  HASH_TABLE
#define HASH_TABLE

//header files:
#include "Some_Declaration.h"

//definition:
#define BUCKETS 1000

//class:
class Hash
{
public:
	//constructor:
	Hash();
	//destructor:
	~Hash();

public:
	//Hashtable establishment and fixing:
	int Hash_Key(char *name);
	int Hash_Key(user *user_info);

	void Hash_Expand(user *user_info);
	void Hash_Amend(user *user_info);

	//Hashtable free:
	void Hash_Free();

	//Hashtable actions:
	void Hash_Print();

public:
	int hash_size;
	//the main body of the hash table:
	struct user_node** table_body;
};

#endif