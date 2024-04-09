#include"rewrite.h"
#include"main.h"
#include"initial.h"

extern string flight_add;
extern int today;

void  rewrite()
{
	cout << endl;
	cout << "******查询航班信息******" << endl;
	cout << "请输入您想查询的航班号：";
	string fli_num;
	getline(cin, fli_num);
	for (int i = 0; i < fli_num.size(); i++)
	{
		fli_num[i] = toupper(fli_num[i]);
	}
	string s = certain_flight(fli_num);
	if (s == "nothing")
	{
		cout << endl;
		cout << "******未找到该航班******" << endl;
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
	else
	{
		flight fli = string_to_flight(s);
		flight sec_fli = string_to_flight(s);
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
			if (weekday == fli.dep)
			{
				int num = fli.from.length();
				if (fli.from.length() == 6)
				{
					fli.from += "　　";
				}
				else if (fli.from.length() == 9)
				{
					fli.from += "　";
				}
				if (fli.to.length() == 6)
				{
					fli.to += "　　";
				}
				else if (fli.to.length() == 9)
				{
					fli.to += "　";
				}


				if (day < today)
				{
					fli.dep = "下" + fli.dep;
					fli.arr = "下" + fli.arr;
				}
				else if (day == 7 && fli.dep != fli.arr)
				{
					fli.dep = fli.dep + "　";
					fli.arr = "下" + fli.arr;
				}
				else
				{
					fli.dep = fli.dep + "　";
					fli.arr = fli.arr + "　";
				}
				break;
			}

		}
		cout << " __________________________________________________________________________________________________________" << endl;

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
		cout << " ----------------------------------------------------------------------------------------------------------" << endl;

		cout << "丨" << setw(6) << left << fli.fli_num << "丨";
		cout << setw(15) << fli.air_num << "丨";
		cout << setw(12) << fli.from << "丨";
		cout << setw(12) << fli.to << "丨";
		cout << setw(11) << fli.dep << "丨";
		cout << setw(11) << fli.arr << "丨";
		cout << setw(6) << (to_string(fli.fir_num)) << "丨";
		cout << setw(5) << fli.fir_pri << "丨";
		cout << setw(6) << to_string(fli.bus_num) << "丨";
		cout << setw(4) << fli.bus_pri << "丨";
		cout << setw(6) << to_string(fli.eco_num) << "丨";
		cout << setw(4) << fli.eco_pri << "丨" << endl;

		cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
		cout << endl;
		cout << "******按下任意键进行下一步操作******" << endl;

		int ch;
		while (1)
		{
			if (_kbhit())
			{
				ch = _getch();
				if (ch != NULL)
				{
					break;
				}
			}
		}
		cout << "（1）修改该航班信息 （2）继续查询 （3）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";

			goto 选择操作;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>3)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作;
		}
		switch (operate)
		{
		case 1:
			rewrite_modify(sec_fli);
			break;
		case 2:
			rewrite();
			break;
		case 3:
			main();
			break;
		}
			

		
	}
}


void rewrite_modify(flight& fli)
{
	cout << endl;
	cout << "******修改航班信息******" << endl;
	cout << "请逐行修改（如果不修改，按“Enter“键即可）：" << endl;
	cout << "飞机号：";
	input(fli.air_num);
	cout << "出发地：";
	input(fli.from);
	cout << "目的地：";
	input(fli.to);
	cout << "起飞时间：";
	input(fli.arr);
	cout << "降落时间：";
	input(fli.dep);
	cout << "头等舱余票：";
	input(fli.fir_num);
	cout << "头等舱票价：";
	input(fli.fir_pri);
	cout << "商务舱余票：";
	input(fli.bus_num);
	cout << "商务舱票价：";
	input(fli.bus_pri);
	cout << "经济舱余票：";
	input(fli.eco_num);
	cout << "经济舱票价：";
	input(fli.eco_pri);
	string new_inf = fli.fli_num + " " + fli.air_num + " " + fli.from + " " + fli.to + " " + fli.dep + " " + fli.arr + " " + to_string(fli.fir_num) + " " + fli.fir_pri + " " + to_string(fli.bus_num) + " " + fli.bus_pri + " " + to_string(fli.eco_num) + " " + fli.eco_pri;
	flight sec_fli = string_to_flight(new_inf);
	
	cout << "请确认您的修改：" << endl;
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
		if (weekday == fli.dep)
		{
			int num = fli.from.length();
			if (fli.from.length() == 6)
			{
				fli.from += "　　";
			}
			else if (fli.from.length() == 9)
			{
				fli.from += "　";
			}
			if (fli.to.length() == 6)
			{
				fli.to += "　　";
			}
			else if (fli.to.length() == 9)
			{
				fli.to += "　";
			}


			if (day < today)
			{
				fli.dep = "下" + fli.dep;
				fli.arr = "下" + fli.arr;
			}
			else if (day == 7 && fli.dep != fli.arr)
			{
				fli.dep = fli.dep + "　";
				fli.arr = "下" + fli.arr;
			}
			else
			{
				fli.dep = fli.dep + "　";
				fli.arr = fli.arr + "　";
			}
			break;
		}

	}
	cout << " __________________________________________________________________________________________________________" << endl;

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
	cout << " ----------------------------------------------------------------------------------------------------------" << endl;

	cout << "丨" << setw(6) << left << fli.fli_num << "丨";
	cout << setw(15) << fli.air_num << "丨";
	cout << setw(12) << fli.from << "丨";
	cout << setw(12) << fli.to << "丨";
	cout << setw(11) << fli.dep << "丨";
	cout << setw(11) << fli.arr << "丨";
	cout << setw(6) << (to_string(fli.fir_num)) << "丨";
	cout << setw(5) << fli.fir_pri << "丨";
	cout << setw(6) << to_string(fli.bus_num) << "丨";
	cout << setw(4) << fli.bus_pri << "丨";
	cout << setw(6) << to_string(fli.eco_num) << "丨";
	cout << setw(4) << fli.eco_pri << "丨" << endl;

	cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	cout << endl;
	cout << "是否确定修改？如过确定，请输入“确定”（否则，输入“取消）：";
	string decide;
确定:
	getline(cin, decide);
	if (decide == "确定")
	{
		cout << endl;
		cout << "正在修改......" << endl;
		fli = sec_fli;
		while (fli.fir_num > 0 && wait_suc(fli.fli_num, "头等舱"))
		{
			fli.fir_num--;
		}
		while (fli.bus_num > 0 && wait_suc(fli.fli_num, "商务舱"))
		{
			fli.bus_num--;
		}
		while (fli.eco_num > 0 && wait_suc(fli.fli_num, "经济舱"))
		{
			fli.eco_num--;
		}
		string reinf= fli.fli_num + " " + fli.air_num + " " + fli.from + " " + fli.to+" " + fli.dep + " " + fli.arr + " " + to_string(fli.fir_num) + " " + fli.fir_pri + " " + to_string(fli.bus_num) + " " + fli.bus_pri + " " + to_string(fli.eco_num) + " " + fli.eco_pri ;
		modify(flight_add, fli.fli_num, reinf);
		cout << "******修改成功******" << endl;
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
	else if (decide == "取消")
	{
		string ss = certain_flight(fli.fli_num);
		fli = string_to_flight(ss);
		cout << endl;
		cout << "******已取消修改******"<<endl;
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
		cout << endl;
		cout << "（1）修改该航班信息 （2）继续查询 （3）返回主菜单" << endl;
		cout << "请选择您想进行的下一步操作序号：";
		string _wait;
		int operate;
	选择操作9:
		getline(cin, _wait);
		if (!is_legal(_wait))
		{
			cout << "输入内容无效，请重新输入:";

			goto 选择操作9;
		}
		operate = to_int(_wait);
		if (operate < 1 || operate>3)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作9;
		}
		switch (operate)
		{
		case 1:
			rewrite_modify(fli);
			break;
		case 2:
			rewrite();
			break;
		case 3:
			main();
			break;
		}

	}
	else
	{
		cout << "输入内容无效，请重新输入:";
		goto 确定;
	}


}

void input(string& old)
{
	string newinf;
	getline(cin, newinf);
	if (newinf == "")
	{

	}
	else
	{
		old = newinf;
	}
}

void input(int& old)
{
	string newinf;
	getline(cin, newinf);
	if (newinf == "")
	{

	}
	else
	{
		old = atoi(newinf.c_str());
	}
}
