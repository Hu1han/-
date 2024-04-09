#pragma once
#include"wait.h"
using namespace std;

void my();

void my_display(vector<flight>& ordered,vector<string> choice, bool is_wait = false);

void back(vector<flight> myorder, vector<string> choice);

void mywait();

void back_wait(vector<flight> waited, vector<string> choice);