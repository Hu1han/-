#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"initial.h"
#include<ctime>
#include<iomanip>



using namespace std;
void search();
void display(vector<flight> &list);
string certain_user(string user_name);
string certain_flight(string fli_name);
string certain_wait(string fli_name);
flight string_to_flight(string certain_flight);

