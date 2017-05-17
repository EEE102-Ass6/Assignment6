//source file: the class of the data structure: Hashtable (detailed description).

using namespace std;

//header file:
#include <iostream>
#include "(Hashtable)_Wjh_Assignment6.h"

//constructor:
Hash::Hash() {
	//initialize the size of the hashtable:
	hash_size = 0;
	//initialize the body of the data structure (the process of memory allocation):
	table_body = (struct user_node**)malloc(BUCKETS * sizeof(struct user_node*));
	for (int i = 0; i < BUCKETS; i++) {
		table_body[i] = (struct user_node*)malloc(sizeof(struct user_node));
		table_body[i]->next = NULL;
		//memory allocation process for hashtable.
	}
	//the announcement:
	cout << "Hashtable is established!" << endl;
}
//destructor:
Hash::~Hash() {
	//the destructor is called successfully.
}

//selfdefined functions (functional):
int Hash::Hash_Key(char *name) {	//return value: "the hash key"
	int key = 0;

	return key;
}

int Hash::Hash_Key(struct user *user_info) {	//return value: "the hash key"
	int key = 0;

	return key;
}

void Hash::Hash_Expand(struct user *user_info) {
	//hash key calculation:
	int key = Hash_Key(user_info);

	struct user_node *head;
	head = table_body[key];

	while (head->next != NULL)
		head = head->next;	//move to the last node.

	head->next = (struct user_node*)malloc(sizeof(struct user_node));	//memory allocation
	head = head->next;
	head->next = NULL;

	//value assigning (add):
	head->

	//total size increased.
	(this->hash_size)++;
}

void Hash::Hash_Amend(struct user *user_info) {
	//hash key calculation:
	int key = Hash_Key(user_info);

	struct user_node *head;
	head = table_body[key];

	while (head->next != NULL) {	//to move to the last node (linked-list).
		head = head->next;

		//making comparison:
	}

	//value assigning (amend):
	head->
	
}

//Hashtable free:
void Hash::Hash_Free(void) {
	struct user_node *head, *move, *store;
	for (int i = 0; i < BUCKETS; i++) {
		head = table_body[i];
		move = head;
		while ((move->next) != NULL) {
			store = move->next;
			free(move);
			move = store;
		}
	}
	free(table_body);
}

//Actions:
void Hash::Hash_Print(void) {
	struct user_node *head;
	printf("Hashtable size: %d.\n", hash_size);
	for (int i = 0; i < BUCKETS; i++) {	//print out accounts in each busket
		head = this->table_body[i];
		printf("%d. bucket No.%d\n", i, i + 1);
		while ((head->next) != NULL) {
			head = head->next;	//move to the last node.
			
		}	//show the principle of the hashtable
	}
	//the announcement:
	printf("Reading hashtable success!\n");
	std::system("PAUSE");
}