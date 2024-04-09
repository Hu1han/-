#pragma once
#include"start.h"
using namespace std;

void turn(string from, string to);

int int_day(string day);

void display_turn(vector<vector<flight>>& turns);

void order_turn(vector<vector<flight>>& turns);

void deal(int num, int rank, int i, string choice);
