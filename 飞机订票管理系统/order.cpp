#pragma once
#include"order.h"
#include"wait.h"
#include"main.h"


void modify(string address,string goal,string mod)//找特定航班，修改其信息;若不存在，则添加
{
	ifstream in;
	ofstream out;
	string retext ="";
	string s;
	in.open(address);
	bool exist = false;
	while (getline(in, s))
	{
		istringstream flight(s);
		string num;
		getline(flight, num, ' ');
		if (exist == false&&num == goal)
		{
			if (mod != "")
			{
				retext = retext + mod + "\n";
			}
			
			exist = true;
			continue;
		}
		retext = retext + s + "\n";
	}
	if (exist == false)
	{
		retext = retext + mod;
	}
	in.close();
	out.open(address);
	out << retext;
	out.close();
}

extern vector<flight> list;
extern string log_name;
extern string user_add;

void order(vector<flight> f_t)
{
	cout << endl;
	cout << "******订票******" << endl;
	cout << "请输入您想购买的航班序号:";
	string orders;
	int ord ;
	stringstream Order;
	label1:
	getline(cin,orders);
	for (char word : orders)
	{
		if (word < 49 or word>57)
		{
			cout << "输入内容无效，请重新输入:";
			goto label1;
		}
	}
	Order.clear();
	Order << orders;
	Order >> ord;
	if (ord > f_t.size())
	{
		cout << "输入内容无效，请重新输入:";
		goto label1;
	}

	
	cout << "舱位等级：（1）头等舱 （2）商务舱 （3）经济舱" << endl;
	cout << "请输入您想购买的舱位等级序号:" ;
	string put;
	stringstream ran;
	int rank=10;

	label2:
	getline(cin, put);
	for (char word : put)
	{
		if (word < 49 or word>57)
		{
			cout << "输入内容无效，请重新输入:";
			goto label2;
		}
	}
	ran.clear();
	ran << put;
	ran >> rank;
	string choice;
	switch (rank)
	{
	case 1:
		choice = "头等舱";
		break;
	case 2:
		choice = "商务舱";
		break;
	case 3:
		choice = "经济舱";
		break;
	default:
		cout << "输入内容无效，请重新输入:";
		goto label2;
	}
	cout << endl;
	cout << "******请确认您的订单******"<<endl;
	cout << "航班号：" << f_t[ord - 1].fli_num<<endl;
	cout << "飞机号：" << f_t[ord - 1].air_num << endl;
	cout << "出发地：" << f_t[ord - 1].from << endl;
	cout << "目的地：" << f_t[ord - 1].to << endl;
	cout << "起飞时间：" << f_t[ord - 1].dep<< endl; 
	cout << "降落时间：" << f_t[ord - 1].arr << endl;
	cout << "舱位等级：" << choice << endl;
	cout << "如果确认订单，请输入“确认”(否则，输入“取消”):";
	string decide;
	确认:
	getline(cin,decide);
	if (decide == "确认")
	{
		string fli_num = f_t[ord - 1].fli_num;
		cout << endl;
		cout << "正在为您查询余票量......" << endl;
		initial();
		bool left = true;
		int num;
		int i=0;
		for (flight fli : list)
		{
			if (fli.fli_num == fli_num)
			{
				switch (rank)
				{
				case 1:
					num = fli.fir_num-1;
					break;
				case 2:
					num = fli.bus_num-1;
					break;
				case 3:
					num = fli.eco_num-1;
					break;
				}
				if (num >=0)
				{
					break;
				}
				else
				{
					left = false;
					break;
				}
				break;
			}
			i++;
		}
		if (left == false)
		{
			cout << endl;
			cout << "******抱歉，余票不足，您可以选择订购其他航班或者候补******"<<endl;
			cout << "（1）候补 （2）选择其他航班或舱位 （3）继续查询（4）返回主菜单" << endl;
			cout << "请选择您想进行的下一步操作序号：";
			string _wait;
			int operate;
			选择操作1:
			getline(cin, _wait);
			if (!is_legal(_wait))
			{
				cout << "输入内容无效，请重新输入:";
				goto 选择操作1;
			}
			operate = to_int(_wait);
			if (operate<1||operate>4)
			{
				cout << "输入内容无效，请重新输入:";
				goto 选择操作1;
			}
			switch (operate)
			{
			case 1:
				cout << endl;
				cout << "正在为您候补......" << endl;
				wait(list[i].fli_num,choice);
				cout << "******候补成功******" << endl;
				cout << endl;
				cout << "******按下“Esc”返回主界面******" << endl;
				int ch;
				while (1) {
					if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
						ch = _getch();
						if (ch == 27)
						{
							break;
						}//当按下ESC时循环，ESC键的键值时27.
					}
				}
				main();
				break;
			case 2:
				order(f_t);
				break;
			case 3:
				search();
				break;
			case 4:
				main();
				break;
			}

		}
		else
		{
			cout << "余票充足,正在完成交易......" << endl;
			string reflight;// = list[i].fli_num + " " + list[i].air_num + " " + list[i].from + " " + list[i].to + " " + list[i].dep + " " + list[i].arr + " " + to_string(list[i].fir_num) + " " + list[i].fir_pri + " " + to_string(list[i].bus_num) + " " + list[i].bus_pri + " " + to_string(list[i].eco_num) + " " + list[i].eco_pri;
			switch (rank)
			{
			case 1:
				reflight = list[i].fli_num + " " + list[i].air_num + " " + list[i].from + " " + list[i].to + " " + list[i].dep + " " + list[i].arr + " " + to_string(num) + " " + list[i].fir_pri + " " + to_string(list[i].bus_num) + " " + list[i].bus_pri + " " + to_string(list[i].eco_num) + " " + list[i].eco_pri;
				break;
			case 2:
				reflight = list[i].fli_num + " " + list[i].air_num + " " + list[i].from + " " + list[i].to + " " + list[i].dep + " " + list[i].arr + " " + to_string(list[i].fir_num) + " " + list[i].fir_pri + " " + to_string(num) + " " + list[i].bus_pri + " " + to_string(list[i].eco_num) + " " + list[i].eco_pri;
				break;
			case 3:
				reflight = list[i].fli_num + " " + list[i].air_num + " " + list[i].from + " " + list[i].to + " " + list[i].dep + " " + list[i].arr + " " + to_string(list[i].fir_num) + " " + list[i].fir_pri + " " + to_string(list[i].bus_num) + " " + list[i].bus_pri + " " + to_string(num) + " " + list[i].eco_pri;
				break;
			}
			extern string flight_add;
			modify(flight_add, f_t[ord - 1].fli_num, reflight);
			string add_inf = list[i].fli_num + " " + choice;
			string reinf = reinformation(log_name, add_inf);
			modify(user_add,log_name, reinf);
			cout << "******恭喜您已完成交易******" << endl;
			cout << endl;
			cout << "******按下“Esc”返回主界面******" << endl;
			int ch;
			while (1) {
				if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
					ch = _getch();
					if (ch == 27)
					{
						break;
					}//当按下ESC时循环，ESC键的键值时27.
				}
			}
			main();
		}
	}
	else if (decide == "取消")
	{
		cout << endl;
		cout << "******订单已取消******" << endl;
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
	else
	{
		cout << "输入内容无效，请重新输入:";
		goto 确认;
	}

}

string reinformation(string name,string reinf, bool is_order)
{
	istringstream f_r(reinf);
	string fli;
	string ran;
	getline(f_r, fli,' ');
	getline(f_r, ran, ' ');
	if (is_order == true)
	{
		string s = certain_user(name);
		s = s + " " + reinf;
		return s;
	}
	else
	{
		vector<string> inf;
		string s = certain_user(name);
		istringstream is(s);
		string each;
		while (getline(is, each, ' '))
		{
			inf.push_back(each);
		}
		
		for (int i = 0; i < inf.size()-1; i++)
		{
			if (inf[i] == fli&& inf[i+1] == ran)
			{
				inf.erase(inf.begin()+i);
				inf.erase(inf.begin() + i);
				break;
			}
		}
		string information=inf[0];
		for (int i = 1; i < inf.size(); i++)
		{
			information = information +" "+ inf[i];
		}
		return information;
	}
}

bool is_legal(string s)
{
	for (char word : s)
	{
		if (word < 49 or word>57)
		{
			return false;
		}
	}
	return true;
}

int to_int(string s)
{
	int i = atoi(s.c_str());
	return i;
}