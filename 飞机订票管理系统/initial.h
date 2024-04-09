#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<sstream>
#include <conio.h>

using namespace std;

void initial();

struct flight
{
	string fli_num;
	string air_num;
	string from;
	string to;
	string dep;
	string arr;
	int fir_num;
	string fir_pri;
	int bus_num;
	string bus_pri;
	int eco_num;
	string eco_pri;
};


