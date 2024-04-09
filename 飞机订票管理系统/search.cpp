#include"search.h"
#include"order.h"
#include"main.h"
#include"turn.h"

extern string user_add;
extern string flight_add;
extern string wait_add;
extern vector<flight> list;
vector<flight> f_t;
string from;
string to;
int today;

void search()//查询并排序
{
	initial();
	cout << endl;
	cout << "******查询******" << endl;
	f_t.clear();
	cout << "请输入出发地：";
	getline(cin, from);
	cout << "请输入目的地：";
	getline(cin, to);
	int sum = list.size();
	for (int i = 0; i < sum; i++)
	{
		if (list[i].from == from && list[i].to == to)
		{
			//cout << list[i].fli_num + " " + list[i].air_num + " " + list[i].from + " " + list[i].to << +" " + list[i].dep + " " + list[i].arr + " " + to_string(list[i].fir_num) + " " + list[i].fir_pri + " " + to_string(list[i].bus_num) + " " + list[i].bus_pri + " " + to_string(list[i].eco_num) + " " + list[i].eco_pri << endl;
			f_t.push_back(list[i]);
		}
	}
	
	int ft_num = f_t.size();
	flight k;
	int t;
	for (int i = 0; i<ft_num-1; i++)//按价格总排序
	{
		t = i;
		for (int j = i+1; j < ft_num; j++)
		{

			if (f_t[t].eco_pri > f_t[j].eco_pri)
			{
				t = j;
			}
		}
		k = f_t[i];
		f_t[i] = f_t[t];
		f_t[t] = k;
	}

	display(f_t);

}

void display(vector<flight> &f_t)//显示
{
	struct tm* tm;
	time_t	tim;
	tim = time(0);
	tm = localtime(&tim);
	today = tm->tm_wday;
	if (today == 0)
	{
		today = 7;
	}

	int day;
	for (int i = 0; i < 7; i++)
	{
		day = today + i;
		string weekday;
		if (day > 7)
		{
			day -= 7;
		}
		switch (day)
		{
		case 1:
			weekday = "周一";
			break;
		case 2:
			weekday = "周二";
			break;
		case 3:
			weekday = "周三";
			break;
		case 4:
			weekday = "周四";
			break;
		case 5:
			weekday = "周五";
			break;
		case 6:
			weekday = "周六";
			break;
		case 7:
			weekday = "周日";
			break;
		}
		int ft_num = f_t.size();
		for (int j = 0; j < ft_num; j++)//按日期排序
		{
			if (weekday == f_t[j].dep)
			{
				int num = f_t[j].from.length();
				if (f_t[j].from.length() == 6)
				{
					f_t[j].from +="　　";
				}
				else if (f_t[j].from.length() ==9)
				{
					f_t[j].from += "　";
				}
				if (f_t[j].to.length() == 6)
				{
					f_t[j].to += "　　";
				}
				else if (f_t[j].to.length() == 9)
				{
					f_t[j].to += "　";
				}


				if (day < today)
				{
					f_t[j].dep = "下" + f_t[j].dep;
					f_t[j].arr = "下" + f_t[j].arr;
				}
				else if (day == 7&& f_t[j].dep!= f_t[j].arr)
				{
					f_t[j].dep = f_t[j].dep+ "　";
					f_t[j].arr = "下" + f_t[j].arr ;
				}
				else
				{
					f_t[j].dep = f_t[j].dep + "　";
					f_t[j].arr = f_t[j].arr + "　";
				}
				f_t.push_back(f_t[j]);
				f_t.erase(f_t.begin() + j);
				j--;
				ft_num--;
			}
		}

	}
	cout << " ________________________________________________________________________________________________________________" << endl;
	cout << "丨" << setw(6) << left << "序号";
	cout << "丨" << setw(8) <<left<< "航班号" << "丨"; 
	cout << setw(17) << "飞机号　" << "丨";
	cout << setw(8) << "出发地　" << "丨";
	cout << setw(6) << "目的地　" << "丨";
	cout << setw(12) <<"起飞时间" << "丨";
	cout << setw(12) << "降落时间" << "丨";
	cout << setw(4) << "头等舱" << "丨";
	cout << setw(6) << "(元)" << "丨";
	cout << setw(5) << "商务舱" << "丨";
	cout << setw(5) << "(元)" << "丨";
	cout << setw(9) << "经济舱" << "丨";
	cout << setw(5) << "(元)" << "丨" << endl;
	//cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	cout << " ----------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < f_t.size(); i++)
	{
		cout << "丨" << setw(4) << left << i + 1;
		cout << "丨" << setw(6) <<left<< f_t[i].fli_num<<"丨";
		cout << setw(15)<<f_t[i].air_num << "丨";
		cout << setw(12) << f_t[i].from << "丨";
		cout << setw(12) << f_t[i].to << "丨";
		cout << setw(11) << f_t[i].dep << "丨";
		cout << setw(11) << f_t[i].arr << "丨";
		cout << setw(6) << (to_string(f_t[i].fir_num)) << "丨";
		cout << setw(5) << f_t[i].fir_pri << "丨";
		cout << setw(6)<<to_string(f_t[i].bus_num) << "丨";
		cout << setw(4)<< f_t[i].bus_pri << "丨";
		cout << setw(6) << to_string(f_t[i].eco_num) << "丨";
		cout << setw(4) << f_t[i].eco_pri << "丨" << endl;

	}
	cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	if (f_t.size() == 0)
	{
		cout << "******抱歉，不存在相关航班******" << endl;
	}
	cout << endl;
	cout << "******按下任意键进行下一步操作******" << endl;

	int ch;
	while (1) {
		if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			ch = _getch();
			if (ch != NULL)
			{
				break;
			}//当按下ESC时循环，ESC键的键值时27.
		}
	}
	if (f_t.size() == 0)
	{
		cout << "（1）查询转机方案 （2）继续查询 （3）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作5:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作5;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>3)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作5;
		}
		switch (operate)
		{
		case 1:
			turn(from,to);
			break;
		case 2:
			search();
			break;
		case 3:
			main();
			break;
		}
	}

	cout << "（1）订票 （2）继续查询 （3）返回主菜单" << endl;
	cout << "请选择您想进行的下一步操作序号：";
	string _wait;
	int operate;
选择操作4:
	getline(cin, _wait);
	if (!is_legal(_wait))
	{
		cout << "输入内容无效，请重新输入:";

		goto 选择操作4;
	}
	operate = to_int(_wait);
	if (operate < 1 || operate>3)
	{
		cout << "输入内容无效，请重新输入:";
		goto 选择操作4;
	}
	switch (operate)
	{
	case 1:
		order(f_t);
		break;
	case 2:
		search();
		break;
	case 3:
		main();
		break;
	}
}

string certain_user(string user_name)
{
	ifstream in;
	in.open(user_add);
	string inf;
	while (getline(in, inf))
	{
		istringstream Inf(inf);
		string name;
		getline(Inf, name, ' ');
		if (name == user_name)
		{
			in.close();

			//cout << inf;
			return inf;
		}
	}
	return "nothing";
}

string certain_flight(string fli_name)
{
	ifstream in;
	in.open(flight_add);
	string inf;
	while (getline(in, inf))
	{
		istringstream Inf(inf);
		string name;
		getline(Inf, name, ' ');
		if (name == fli_name)
		{
			in.close();
			return inf;
		}
	}
	return "nothing";
}

string certain_wait(string fli_name)
{
	ifstream in;
	in.open(wait_add);
	string inf;
	while (getline(in, inf))
	{
		istringstream Inf(inf);
		string name;
		getline(Inf, name, ' ');
		if (name == fli_name)
		{
			in.close();
			return inf;
		}
	}
	return "nothing";
}

flight string_to_flight(string certain_flight)
{
	istringstream is_line(certain_flight);
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
	//cout << each_fli.eco_pri;
	return each_fli;
}

