#include"wait.h"

extern string log_name;
extern string wait_add;
extern string user_add;
extern string flight_add;

void wait (string fli_name,string rank)
{
	string s = certain_wait(fli_name);
	if (s== "nothing")
	{
		s = fli_name + " " + log_name+" "+rank;
	}
	else
	{
		s = s + " " + log_name+" "+rank;
	}
	modify(wait_add, fli_name, s);
}

bool wait_suc(string fli_name, string rank)
{
	string s = certain_wait(fli_name);
	vector<string> waits;
	istringstream is(s);
	string each;
	while (getline(is, each, ' '))
	{
		waits.push_back(each);
	}
	for (int i = 2; i < waits.size(); i = i + 2)
	{
		if (waits[i] == rank)
		{
			string reinf = reinformation(waits[i - 1], waits[0]+" "+waits[i]);
			modify(user_add, waits[i - 1], reinf);
			waits.erase(waits.begin() + i - 1);
			waits.erase(waits.begin() + i - 1);
			string rewait = waits[0];
			for (int j = 1; j < waits.size(); j++)
			{
				rewait =rewait+ " " + waits[j];
			}
			if (rewait == waits[0])
			{
				rewait = "";
			}
			modify(wait_add, waits[0], rewait);
			return true;
		}
	}
	return false;

}

void return_to_flight(string fli_name, string rank)
{
	string s = certain_flight(fli_name);
	flight fli = string_to_flight(s);
	if (rank == "头等舱")
	{
		fli.fir_num++;
	}
	else if (rank == "经济舱")
	{
		fli.bus_num++;
	}
	else
	{
		fli.eco_num++;
	}
	string reflight = fli.fli_num + " " + fli.air_num + " " + fli.from + " " + fli.to + " " + fli.dep + " " + fli.arr + " " + to_string(fli.fir_num) + " " + fli.fir_pri + " " + to_string(fli.bus_num) + " " + fli.bus_pri + " " + to_string(fli.eco_num) + " " + fli.eco_pri;
	modify(flight_add, fli.fli_num, reflight);
}