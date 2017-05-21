/*
* File      :Administrator.cpp
* Author: Zhao zhihe£¨Kyrie£©
* ID number: 1405180
* Description: This file is to implement the function concerning to information of the SUDO AUTHORITY.
* Change Logs:
* Date           Author          Notes
* 2017-05-17     Kyrie.Zhao      Implement the interfaces
*/
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
