# Assignment6
EEE102 assignment 6

## Taxi Company Management System

> This is a company management system especially for the Taxi Company. The basis source code is C++.

### Introduction

For an easy way to create certain types of extension with no coding necessary, check out Brett Terpstra's [PopMaker](http://brettterpstra.com/2014/05/12/popmaker-popclip-extension-generator/) app.

Here are some external "how to" guides for creating extensions:

- [API](/docs/API.pdf)
- [Report](/docs/Report.pdf)

### Interface

The user interface is used the Linux shell style. User can use the 'help' command to infer the useage of the system.

There are two basic authorities for the user. **Normal** user will be the first layer, these normal user is preset as the drivers to search their own infomation.The second layer has a higher authority, **Administrater**, to do the management and operations to the objects.

To provide uncluttered interface and simple views and control, the system simulates LINUX SHELL using C++ codes. There are two threads consisted in the system. The main thread contains function commands, such as registration and editing information. User can call function by inputting corresponding number. The second thread is about system commands, such as exiting the program, returning to previous menu and getting help. User can call system command at any time when the main thread is operating. In particular, a practical system command is designed that is to send database file to a preset e-mail address.

####  **Help** usage 



| command                       | function                                 |
| :---------------------------- | :--------------------------------------- |
| **help**: help[HELP]          | Illustrate the system commands which initially set. |
| **clear**: clear[CLR]         | Directly enter the clear command any information on the current terminal can be cleared. |
| **cd**: cd[CD]                | Get back to the main menu.               |
| **ls (parameter)**: ls[LS]    | Directly display the databases list.     |
| **/-l:**                      | Display all databases list including the size of them. |
| **rm/(option)**: delete[RM]   | Delete the file you choose               |
| **mail/(option)**: mail[MAIL] | Choose a database file to send to the mailbox, the set mailbox is zhaozhihe2333@sina.com |
| **cd**: change directory[CD]  | Switch the working directory to the main menu. |
| **exit**: exit[EXIT]          | Exit the sudo account.                   |
| **quit**: quit[QUIT]          | Quit the software                        |

	 



## Description of file management

- scr: Used to stroe our source code files.
- docs: Used to stroe our documents and Final report:
  - **EEE102_Group Project Guidelines.pdf**
  - **Report.pdf**
  - **API.pdf**
