#pragma once
//the declaration of structure: "node" appears in the data structure.

#ifndef _NODE
#define _NODE

//header file:
#include "(Vehicle)_header.h"
#include "(Driver)_header.h"

//node declaration:
struct vehicle_node;

typedef struct driver_node
{
	Driver _driver;
	//path to the next node:
	driver_node *next;
	//path to the vehicle:
	vehicle_node *_his_car = {NULL};
};

typedef struct vehicle_node
{
	Vehicle _vehicle;
	//path to the next node:
	vehicle_node *next;
	//path to the pilot:
  driver_node *_its_pilot[2]; //= {NULL, NULL};
};

#endif