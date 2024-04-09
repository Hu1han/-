#include"initial.h"

vector<flight> list;

ifstream in;
string flight_add=".//航班.txt";
string wait_add = ".//候补.txt";
string user_add = ".//用户.txt";
string manager_add = ".//管理员.txt";

void initial()
{
	list.clear();
	in.open(flight_add);
	string line;
	while (getline(in, line))
	{
		istringstream is_line(line);
		string each;
		int i = 0;
		string eachs[12];
		while (getline(is_line, each, ' '))
		{
			eachs[i] = each;
			//cout << eachs[i];
			i++;
		}
		flight each_fli = { eachs[0],eachs[1],eachs[2],eachs[3],eachs[4],eachs[5],atoi(eachs[6].c_str()),eachs[7],atoi(eachs[8].c_str()),eachs[9],atoi(eachs[10].c_str()),eachs[11] };
		//cout << each_fli.arr;
		list.push_back(each_fli);
	}
	
	in.close();
}
