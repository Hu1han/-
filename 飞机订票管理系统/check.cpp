#include"check.h"
#include"main.h"

extern string log_name;
extern string wait_add;
extern string user_add;
vector<flight> ordered;
vector<flight> waited;
vector<string> choice;

void my()
{
	cout << endl;
	cout << "******查看订单******" << endl;
	ordered.clear();
	choice.clear();
	string s = certain_user(log_name);
	istringstream inf(s);
	string each;
	vector<string> information;
	while (getline(inf,each, ' '))
	{
		information.push_back(each);
	}
	for (int i = 2; i < (information.size() - 1); i = i + 2)
	{
		string s = certain_flight(information[i]);
		flight fli = string_to_flight(s);
		ordered.push_back(fli);
		choice.push_back(information[i + 1]);
	}
	my_display(ordered, choice);
}

void mywait()
{
	cout << endl;
	cout << "******查看订单******" << endl;
	waited.clear();
	choice.clear();

	ifstream in;
	in.open(wait_add);
	string str;
	while (getline(in, str))
	{
		istringstream is(str);
		string strs;
		vector<string> each;
		while (getline(is, strs,' '))
		{
			each.push_back(strs);
		}
		for (int k = 0; k < each.size(); k++)
		{
			if (each[k] == log_name)
			{
				string s = certain_flight(each[0]);
				flight fli = string_to_flight(s);
				waited.push_back(fli);
				choice.push_back(each[k + 1]);
			}
		}
	}
	in.close();



	
	my_display(waited, choice,true);
}

void my_display(vector<flight>& ordered, vector<string> choice,bool is_wait)
{
	struct tm* tm;
	time_t	tim;
	tim = time(0);
	tm = localtime(&tim);
	int today = tm->tm_wday;
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
		int ft_num = ordered.size();
		for (int j = 0; j < ft_num; j++)//按日期排序
		{
			if (weekday == ordered[j].dep)
			{
				int num = ordered[j].from.length();
				if (ordered[j].from.length() == 6)
				{
					ordered[j].from += "　　";
				}
				else if (ordered[j].from.length() == 9)
				{
					ordered[j].from += "　";
				}
				if (ordered[j].to.length() == 6)
				{
					ordered[j].to += "　　";
				}
				else if (ordered[j].to.length() == 9)
				{
					ordered[j].to += "　";
				}


				if (day < today)
				{
					ordered[j].dep = "下" + ordered[j].dep;
					ordered[j].arr = "下" + ordered[j].arr;
				}
				else if (day == 7)
				{
					ordered[j].dep = ordered[j].dep + "　";
					ordered[j].arr = "下" + ordered[j].arr;
				}
				else
				{
					ordered[j].dep = ordered[j].dep + "　";
					ordered[j].arr = ordered[j].arr + "　";
				}
				ordered.push_back(ordered[j]);
				ordered.erase(ordered.begin() + j);
				j--;
				ft_num--;
			}
		}

	}
	cout << " _______________________________________________________________________________" << endl;
	cout << "丨" << setw(6) << left << "序号";
	cout << "丨" << setw(8) << left << "航班号" << "丨";
	cout << setw(17) << "飞机号　" << "丨";
	cout << setw(8) << "出发地　" << "丨";
	cout << setw(6) << "目的地　" << "丨";
	cout << setw(12) << "起飞时间" << "丨";
	cout << setw(12) << "降落时间" << "丨";
	cout << setw(4) << "舱位等级" << "丨"<<endl;
	//cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	cout << " -------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < ordered.size(); i++)
	{
		cout << "丨" << setw(4) << left << i + 1;
		cout << "丨" << setw(6) << left << ordered[i].fli_num << "丨";
		cout << setw(15) << ordered[i].air_num << "丨";
		cout << setw(12) << ordered[i].from << "丨";
		cout << setw(12) << ordered[i].to << "丨";
		cout << setw(11) << ordered[i].dep << "丨";
		cout << setw(11) << ordered[i].arr << "丨";
		cout << setw(4) << choice[i] << "　丨" << endl;

	}
	cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	if (ordered.size() == 0)
	{
		if (!is_wait)
		{
			cout << "******您目前没有订单******" << endl;
		}
		else
		{
			cout << "******您目前没有候补******" << endl;
		}
	}
	cout << endl;
	if (ordered.size() == 0)
	{
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
	cout << "******按下任意键进行下一步操作******" << endl;

	int ch;
	while (1) {
		if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			ch = _getch();
			if (ch!=NULL)
			{
				break;
			}//当按下ESC时循环，ESC键的键值时27.
		}
	}
	cout << endl;
	if (!is_wait)
	{
		cout << "（1）取消订单（2）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作2:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作2;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>2)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作2;
		}
		switch (operate)
		{
		case 1:
			back(ordered, choice);
			break;
		case 2:
			main();
			break;
		}
	}
	else
	{
		cout << "（1）取消候补（2）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作6:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作6;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>2)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作6;
		}


		switch (operate)
		{
		case 1:
			back_wait(waited, choice);
			break;
		case 2:
			main();
			break;
		}
	}
	
}

void back(vector<flight> myorder, vector<string> choice )
{
	cout << endl;
	cout << "******取消订单******" << endl;
	cout << "请输入您想取消的订单序号：";
	string num;
	选择序号:
	getline(cin, num);
	if (!is_legal(num))
	{
		cout << "输入内容无效，请重新输入:";
		goto 选择序号;
	}
	int number = to_int(num);
	if (number<1 || number>myorder.size())
	{
		cout << "输入内容无效，请重新输入:";
		goto 选择序号;
	}
	cout << endl;
	cout << "******请确认您要取消的订单******" << endl;
	cout << "航班号：" << myorder[number- 1].fli_num << endl;
	cout << "飞机号：" << myorder[number- 1].air_num << endl;
	cout << "出发地：" << myorder[number- 1].from << endl;
	cout << "目的地：" << myorder[number- 1].to << endl;
	cout << "起飞时间：" << myorder[number- 1].dep << endl;
	cout << "降落时间：" << myorder[number- 1].arr << endl;
	cout << "舱位等级：" << choice[number - 1] << endl;
	cout << "如果确认取消该订单，请输入“确认”(否则，输入“撤回”):";
	string decide;
	确认:
	getline(cin, decide);
	if (decide == "确认")
	{
		cout << endl;
		cout << "正在为您取消订单......" << endl;
		string s = certain_wait(myorder[number - 1].fli_num);
		string reinf = reinformation(log_name, myorder[number - 1].fli_num +" "+ choice[number - 1], false);
		modify(user_add, log_name, reinf);
		if (s != "nothing")
		{
			if (wait_suc(myorder[number - 1].fli_num, choice[number - 1]))
			{
			}
			else
			{
				return_to_flight(myorder[number - 1].fli_num, choice[number - 1]);
			}
		}
		else
		{
			return_to_flight(myorder[number - 1].fli_num, choice[number - 1]);
		}

		cout << "******取消订单成功******" << endl;
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
	else if (decide == "撤回")
	{
		cout << endl;
		cout << "******已撤回您的操作******" << endl;
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
		cout << endl;
		cout << "（1）取消订单（2）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作2:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作2;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>2)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作2;
		}
		switch (operate)
		{
		case 1:
			back(ordered, choice);
			break;
		case 2:
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

void back_wait(vector<flight> waited, vector<string> choice)
{
	{
		cout << endl;
		cout << "******取消候补******" << endl;
		cout << "请输入您想取消的候补序号：";
		string num_;
	选择序号:
		getline(cin, num_);
		if (!is_legal(num_))
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择序号;
		}
		int number = to_int(num_);
		if (number<1 || number>waited.size())
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择序号;
		}
		cout << endl;
		cout << "******请确认您要取消的候补******" << endl;
		cout << "航班号：" << waited[number - 1].fli_num << endl;
		cout << "飞机号：" << waited[number - 1].air_num << endl;
		cout << "出发地：" << waited[number - 1].from << endl;
		cout << "目的地：" << waited[number - 1].to << endl;
		cout << "起飞时间：" << waited[number - 1].dep << endl;
		cout << "降落时间：" << waited[number - 1].arr << endl;
		cout << "舱位等级：" << choice[number - 1] << endl;
		cout << "如果确认取消该候补，请输入“确认”(否则，输入“撤回”):";
		string decide;
	确认:
		getline(cin, decide);
		if (decide == "确认")
		{
			cout << endl;
			cout << "正在为您取消候补......" << endl;
			string s = certain_wait(waited[number - 1].fli_num);
			istringstream wait_(s);
			string eve;
			vector<string> every;
			while (getline(wait_, eve, ' '))
			{
				every.push_back(eve);
			}
			for (int m = 0; m < every.size(); m++)
			{
				if (every[m] == log_name && every[m + 1] == choice[number - 1])
				{
					every.erase(every.begin() + m);
					every.erase(every.begin() + m);
					break;
				}
			}
			string reinf ;
			for (int m = 0; m < every.size(); m++)
			{
				reinf += every[m];
			}
			if (reinf == every[0])
			{
				reinf = "";
			}
			modify(wait_add, waited[number - 1].fli_num, reinf);

			cout << "******取消候补成功******" << endl;
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
		else if (decide == "撤回")
		{
			cout << endl;
			cout << "******已撤回您的操作******" << endl;
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
			cout << endl;
			cout << "（1）取消候补（2）返回主菜单" << endl;
			cout << "请选择您想进行的下一步操作序号：";
			string _wait;
			int operate;
		选择操作8:
			getline(cin, _wait);
			if (!is_legal(_wait))
			{
				cout << "输入内容无效，请重新输入:";
				goto 选择操作8;
			}
			operate = to_int(_wait);
			if (operate < 1 || operate>2)
			{
				cout << "输入内容无效，请重新输入:";
				goto 选择操作8;
			}
			switch (operate)
			{
			case 1:
				back_wait(waited, choice);
				break;
			case 2:
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
}