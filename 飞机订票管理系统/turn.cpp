#include"turn.h"
#include"main.h"

extern string user_add;

vector<flight> first;
vector<flight> second;
vector<vector<flight>> all_turn;
extern vector<flight> list;
extern int today;
extern string log_name;


void turn(string from, string to)
{
	all_turn.clear();
	first.clear();
	int sum = list.size();
	for (int i = 0; i < sum; i++)
	{
		if (list[i].from == from)
		{
			first.push_back(list[i]);
		}
	}

	int ft_num = first.size();
	flight k;
	int t;
	for (int m = 0; m < ft_num - 1;m++)
	{
		t = m;
		for (int j = m + 1; j < ft_num; j++)
		{

			if (first[t].eco_pri > first[j].eco_pri)
			{
				t = j;
			}
		}
		k = first[m];
		first[m] = first[t];
		first[t] = k;
	}



	for (int m = 0; m< first.size(); m++)
	{
		second.clear();
		int sum = list.size();
		int day = int_day(first[m].arr);
		if (int_day(first[m].dep)<today|| int_day(first[m].dep)==7)
		{
			day += 7;
		}
		//cout << first[m].to << endl;
		for (int i = 0; i < sum; i++)
		{
			if (list[i].from == first[m].to && list[i].to == to)
			{
				second.push_back(list[i]);
			}
		}

		int sec_num = second.size();
		for (int j = 0; j < second.size(); j++)
		{
			int sec_day = int_day(second[j].dep);
			if (sec_day < today)
			{
				sec_day += 7;
			}
			if (!(sec_day == day))
			{
				second.erase(second.begin() + j);
				j--;
			}
		}



		int ft_num = second.size();
		flight k;
		int t;
		for (int i = 0; i < ft_num - 1; i++)
		{
			t = i;
			for (int j = i + 1; j < ft_num; j++)
			{

				if (second[t].eco_pri > second[j].eco_pri)
				{
					t = j;
				}
			}
			k = second[i];
			second[i] = second[t];
			second[t] = k;
		}
		if (second.size() == 0)
		{
			continue;
		}
		for (int j = 0; j < second.size(); j++)
		{
			vector<flight> each_turn;
			each_turn.push_back(first[m]);
			each_turn.push_back(second[j]);
			all_turn.push_back(each_turn);
		}
	}

	display_turn(all_turn);
}

int int_day(string day)
{
	if (day == "周一")
	{
		return 1;
	}
	else if (day == "周二")
	{
		return 2;
	}
	else if (day == "周三")
	{
		return 3;
	}
	else if (day == "周四")
	{
		return 4;
	}
	else if (day == "周五")
	{
		return 5;
	}
	else if (day == "周六")
	{
		return 6;
	}
	else
	{
		return 7;
	}
}

void display_turn(vector<vector<flight>>& turns)
{
	cout << " ________________________________________________________________________________________________________________" << endl;
	cout << "丨" << setw(6) << left << "序号";
	cout << "丨" << setw(8) << left << "航班号" << "丨";
	cout << setw(17) << "飞机号　" << "丨";
	cout << setw(8) << "出发地　" << "丨";
	cout << setw(6) << "目的地　" << "丨";
	cout << setw(12) << "起飞时间" << "丨";
	cout << setw(12) << "降落时间" << "丨";
	cout << setw(4) << "头等舱" << "丨";
	cout << setw(6) << "(元)" << "丨";
	cout << setw(5) << "商务舱" << "丨";
	cout << setw(5) << "(元)" << "丨";
	cout << setw(9) << "经济舱" << "丨";
	cout << setw(5) << "(元)" << "丨" << endl;
	cout << " ----------------------------------------------------------------------------------------------------------------" << endl;

	for (int m = 0; m < turns.size(); m++)
	{

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
			int ft_num = turns[m].size();
			for (int j = 0; j < ft_num; j++)
			{
				if (weekday == turns[m][j].dep)
				{
					int num = turns[m][j].from.length();
					if (turns[m][j].from.length() == 6)
					{
						turns[m][j].from += "　　";
					}
					else if (turns[m][j].from.length() == 9)
					{
						turns[m][j].from += "　";
					}
					if (turns[m][j].to.length() == 6)
					{
						turns[m][j].to += "　　";
					}
					else if (turns[m][j].to.length() == 9)
					{
						turns[m][j].to += "　";
					}


					if (day < today)
					{
						turns[m][j].dep = "下" + turns[m][j].dep;
						turns[m][j].arr = "下" + turns[m][j].arr;
					}
					else if (day == 7&& (turns[m][j].dep!= turns[m][j].arr))
					{
						turns[m][j].dep = turns[m][j].dep+ "　";
						turns[m][j].arr = "下" + turns[m][j].arr ;
					}
					else
					{
						turns[m][j].dep = turns[m][j].dep + "　";
						turns[m][j].arr = turns[m][j].arr + "　";
					}
					turns[m].push_back(turns[m][j]);
					turns[m].erase(turns[m].begin() + j);
					j--;
					ft_num--;
				}
			}

		}

		bool turn_num = true;
		for (int i = 0; i < turns[m].size(); i++)
		{
			if (turn_num)
			{
				cout << "丨" << setw(4) << left << m + 1;
				turn_num = false;
			}
			else
			{
				cout << "丨" << setw(4)<<' ';
			}
			cout << "丨" << setw(6) <<left<< turns[m][i].fli_num<<"丨";
			cout << setw(15)<<turns[m][i].air_num << "丨";
			cout << setw(12) << turns[m][i].from << "丨";
			cout << setw(12) << turns[m][i].to << "丨";
			cout << setw(11) << turns[m][i].dep << "丨";
			cout << setw(11) << turns[m][i].arr << "丨";
			cout << setw(6) << (to_string(turns[m][i].fir_num)) << "丨";
			cout << setw(5) << turns[m][i].fir_pri << "丨";
			cout << setw(6)<<to_string(turns[m][i].bus_num) << "丨";
			cout << setw(4)<< turns[m][i].bus_pri << "丨";
			cout << setw(6) << to_string(turns[m][i].eco_num) << "丨";
			cout << setw(4) << turns[m][i].eco_pri << "丨" << endl;

		}
		if (m != (turns.size() - 1))
		{
			cout << " ----------------------------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
		}
		

	}
	if (all_turn.size() == 0)
	{
		cout << "******抱歉，暂不存在相关转机方案******" << endl;
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

	if (all_turn.size() == 0)
	{
		cout << "（1）继续查询 （2）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	确认5:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入：";
			goto 确认5;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>3)
		{
			cout << "输入内容无效，请重新输入：";
			goto 确认5;
		}
		switch (operate)
		{
		case 1:
			search();
			break;
		case 2:
			main();
			break;
		}
	}

	cout << "（1）订票 （2）继续查询 （3）返回主菜单" << endl;
	cout << "请选择您想进行的下一步操作序号：";
	string _wait;
	int operate;
确认4:
	getline(cin, _wait);
	if (!is_legal(_wait))
	{
		cout << "输入内容无效，请重新输入：";

		goto 确认4;
	}
	operate = to_int(_wait);
	if (operate < 1 || operate>3)
	{
		cout << "输入内容无效，请重新输入：";
		goto 确认4;
	}
	switch (operate)
	{
	case 1:
		order_turn(turns);
		break;
	case 2:
		search();
		break;
	case 3:
		main();
		break;
	}
}

void order_turn(vector<vector<flight>>& turns)
{
	cout << endl;
	cout << "******订票******" << endl;
	cout << "请输入您想购买的方案序号:";
	string orders;
	int ord;
	stringstream Order;
label3:
	getline(cin, orders);
	for (char word : orders)
	{
		if (word < 49 or word>57)
		{
			cout << "输入内容无效，请重新输入：";
			goto label3;
		}
	}
	Order.clear();
	Order << orders;
	Order >> ord;
	if (ord > turns.size())
	{
		cout << "输入内容无效，请重新输入：";
		goto label3;
	}
	
	string choices[2];
	int ranks[2];
	cout << "舱位等级：（1）头等舱 （2）商务舱 （3）经济舱" << endl;
	for (int k = 0; k < 2; k++)
	{
		if (k == 0)
		{
			cout << "请输入您想购买到达中转站的舱位等级序号:" ;
		}
		else
		{
			cout << "请输入您想购买到达目的地的舱位等级序号:" ;
		}
		string put;
		stringstream ran;
		int rank;

	label2:
		getline(cin, put);
		for (char word : put)
		{
			if (word < 49 or word>57)
			{
				cout << "输入内容无效，请重新输入：";
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
			cout << "输入内容无效，请重新输入：";
			goto label2;
		}
		choices[k] = choice;
		ranks[k] = rank;
	}

	cout << endl;
	cout << "******请确认您的订单******" << endl;
	cout << "航班号：" << setw(20) << turns[ord - 1][0].fli_num << "航班号：" << turns[ord - 1][1].fli_num << endl;
	cout << "飞机号：" << setw(22) << turns[ord - 1][0].air_num << "飞机号：" << turns[ord - 1][1].air_num << endl;
	cout << "出发地：" << setw(24) << turns[ord - 1][0].from << "出发地：" << turns[ord - 1][1].from << endl;
	cout << "目的地：" << setw(24) << turns[ord - 1][0].to << "目的地：" << turns[ord - 1][1].to << endl;
	cout << "起飞时间：" << setw(21) << turns[ord - 1][0].dep << "起飞时间：" << turns[ord - 1][1].dep << endl;
	cout << "降落时间：" << setw(21) <<turns[ord - 1][0].arr << "降落时间：" << turns[ord - 1][1].arr << endl;
	cout << "舱位等级：" << setw(21)<< choices[0] << "舱位等级：" << choices[1] << endl;
	cout << "如果确认订单，请输入“确认”(否则，输入“取消”):";
	string decide;
	确认:
	getline(cin, decide);
	int nums[2];
	int list_i[2];
	if (decide == "确认")
	{
		cout << endl;
		cout << "正在为您查询余票量......." << endl;
		bool left = true;
		for (int k = 0; k < 2; k++)
		{
			string fli_num = turns[ord - 1][k].fli_num;
			int num;
			int i = 0;
			for (flight fli : list)
			{
				if (fli.fli_num == fli_num)
				{
					initial();
					switch (ranks[k])
					{
					case 1:
						num = fli.fir_num - 1;
						break;
					case 2:
						num = fli.bus_num - 1;
						break;
					case 3:
						num = fli.eco_num - 1;
						break;
					}


					nums[k] = num;

					if (num >= 0)
					{
						break;
					}
					else
					{
						left = false;
						break;
					}

				}
				i++;
			}
			list_i[k] = i;
		}

		if (left == false)
		{
			cout << endl;
			cout << "******抱歉，您所选的方案存在余票不足，您可以选择订购其他航班或者候补******" << endl;
			cout << "（1）候补 （2）选择其他航班或舱位 （3）继续查询（4）返回主菜单" << endl;
			cout << "请选择您想进行的下一步操作序号：";
			string _wait;
			int operate;
		确认1:
			getline(cin, _wait);
			if (!is_legal(_wait))
			{
				cout << "输入内容无效，请重新输入：";
				goto 确认1;
			}
			operate = to_int(_wait);
			if (operate < 1 || operate>4)
			{
				cout << "输入内容无效，请重新输入：";
				goto 确认1;
			}
			switch (operate)
			{
			case 1:
				cout << endl;
				cout << "正在为您办理......" << endl;

				for (int k = 0; k < 2; k++)
				{
					cout << endl;
					if (k == 0)
					{
						cout << "正在处理到达中转站的航班......" << endl;
					}
					else
					{
						cout << "正在处理到达目的地的航班....." << endl;
					}
					deal(nums[k], ranks[k], list_i[k], choices[k]);
				}
				cout << endl;
				cout << "******恭喜您，办理完成******" << endl;
				
				cout << endl;
				cout << "******按下“Esc”返回主界面******" << endl;
				int ch;
				while (1) {
					if (_kbhit()) {
						ch = _getch();
						if (ch == 27)
						{
							break;
						}
					}
				}
				main();
				break;
			case 2:
				order_turn(all_turn);
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
			for (int k = 0; k < 2; k++)
			{
				cout << endl;
				if (k == 0)
				{
					cout << "正在处理到达中转站的航班......." << endl;
				}
				else
				{
					cout << "正在处理到达目的地的航班......" << endl;
				}
				deal(nums[k], ranks[k], list_i[k], choices[k]);
			}
			cout << endl;
			cout << "******恭喜您，办理完成******" << endl;

			cout << endl;
			cout << "******按下“Esc”返回主界面******" << endl;
			int ch;
			while (1) {
				if (_kbhit()) {
					ch = _getch();
					if (ch == 27)
					{
						break;
					}
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
			if (_kbhit()) {
				ch = _getch();
				if (ch != NULL)
				{
					break;
				}
			}
		}
		cout << "（1）订票 （2）继续查询 （3）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	确认4:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入：";

			goto 确认4;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>3)
		{
			cout << "输入内容无效，请重新输入：";
			goto 确认4;
		}
		switch (operate)
		{
		case 1:
			order_turn(all_turn);
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
		cout << "输入内容无效，请重新输入：";
		goto 确认;
	}



}

void deal(int num, int rank,int i,string choice)
{
	if (num >= 0)
	{
		cout << "有余票,正在完成交易......" << endl;
		string reflight;
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
		modify(flight_add, list[i].fli_num, reflight);
		string add_inf = list[i].fli_num + " " + choice;
		string reinf = reinformation(log_name, add_inf);
		modify(user_add, log_name, reinf);
		cout << "******已完成交易******" << endl;
	}
	else
	{
		cout << "正在候补......" << endl;
		wait(list[i].fli_num, choice);
		cout << "候补成功" << endl;
	}
}
