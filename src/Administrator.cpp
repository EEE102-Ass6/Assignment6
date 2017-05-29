#include"Administrator.h"
#include<cstring>
adm_char_t* Admin:: get_account()
{
	return this->account;
}

adm_char_t* Admin::get_password()
{
	return this->password;
}
adm_uint8_t Admin::get_passwd_len()
{
	int tmp = strlen(this->password);
	return (tmp);
}
void Admin::set_newPW(adm_char_t* new_pw)
{	
		this->password = new_pw;
}
