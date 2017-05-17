//header file: the class represents for the data base. All operations revolved around the file is included in this class.

#ifndef  FILE_OPERATION
#define FILE_OPERATION

//header file:

//class:
class File_Operation
{
public:
	//constructor:
	File_Operation();
	//destructor:
	~File_Operation();

public:
	//functional self-defined functions:

private:

};
#endif

struct admin *account_temp = new struct admin;
ifstream acc_hash;
//read only
acc_hash.open("account.dat", ios::in);
if (acc_hash.fail()) {
	cout << "ERROR: Cannot open file 'account.bat'." << endl;
	Sleep(2000); acc_hash.close();
	std::exit(0);
}
else {
	cout << "Hashtable is creating..." << endl;
	for (int i = 0; !acc_hash.eof(); i++) {
		if (!acc_hash.read((char*)account_temp, sizeof(struct admin)))
			break;	//this time, read failed...
		else {
			/*----------Expanding----------*/
			hashtable.Hash_Expand(account_temp);
			this->_position.current_account_num++;
			/*-----------------------------*/
		}
	}
	acc_hash.close();
	cout << "Hashtable inspection complete!" << endl;
}