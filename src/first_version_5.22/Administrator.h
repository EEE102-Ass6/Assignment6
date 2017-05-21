#pragma once
#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include<iostream>
#include "Base.h"
using namespace std;
class Admin 
	{
		protected:
			int a = 1;
			adm_char_t* account = "sudo";
			adm_char_t* password = "1111";

		public:
			Admin() {};
			~Admin() {};
		//	adm_char_t* new_password;
			adm_uint8_t get_passwd_len();
			adm_char_t* get_account();
			adm_char_t* get_password();
			void set_newPW(adm_char_t* new_pw);
	};
#endif // 
