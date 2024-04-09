//#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"main.h"
#include"rewrite.h"

extern vector<flight> list;
extern vector<flight> f_t;
extern string flight_add;
extern bool is_log;
extern bool is_manager;
extern vector<vector<flight>> all_turn;

int main()
{
	if (!is_log)
	{
		start();
	}

	cout << endl;
	cout << "******主菜单******" << endl;
	if (is_manager)
	{
		cout << "（1）查询/修改航班信息 （2）退出程序 （3）退出登录 " << endl;
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
		if (operate < 1 || operate>5)
		{
			cout << "输入内容无效，请重新输入:";
			goto 选择操作9;
		}
		switch (operate)
		{
		case 1:
			rewrite();
			break;
		case 2: {
			cout << endl;
			cout << "是否确定退出程序？如果确定，请输入“确定”（否则，输入“取消”）：";
			string sure;
		确定3:
			getline(cin, sure);
			if (sure == "确定")
			{
				cout << endl;
				cout << "正在退出......" << endl;
				is_log = false;
				main();
			}
			else if (sure == "取消")
			{
				cout << endl;
				cout << "******已取消******" << endl;
				cout << endl;
				cout << "******按下任意键返回主菜单******" << endl;

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
				main();
			}
			else
			{
				cout << "输入内容无效，请重新输入:";
				goto 确定3;
			}
			cout << endl;
			cout << "******欢迎下次使用******" << endl;
			exit(0);
			break; }
		case 3:
			cout << endl;
			cout << "是否确定退出登录？如果确定，请输入“确定”（否则，输入“取消”）：";
			string decide;
		确定2:
			getline(cin, decide);
			if (decide == "确定")
			{
				cout << endl;
				cout << "正在退出......" << endl;
				is_log = false;
				main();
			}
			else if (decide == "取消")
			{
				cout << endl;
				cout << "******已取消******"<<endl;
				cout << endl;
				cout << "******按下任意键返回主菜单******" << endl;

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
				main();
			}
			else
			{
				cout << "输入内容无效，请重新输入:";
				goto 确定2;
			}
			break;
		}
	}
	cout << "（1）查询/订票 （2）查看订单 （3）查看候补（4）退出程序 （5）退出登录" << endl;
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
	if (operate < 1 || operate>5)
	{
		cout << "输入内容无效，请重新输入:";
		goto 选择操作4;
	}
	switch (operate)
	{
	case 1:
		search();
		break;
	case 2:
		my();
		break;
	case 3:
		mywait();
		break;
	case 4: {
		cout << endl;
		cout << "是否确定退出程序？如果确定，请输入“确定”（否则，输入“取消”）：";
		string sure;
		确定4:
		getline(cin, sure);
		if (sure == "确定")
		{
			cout << endl;
			cout << "正在退出......" << endl;
			is_log = false;
			main();
		}
		else if (sure == "取消")
		{
			cout << endl;
			cout << "******已取消******" << endl;
			cout << endl;
			cout << "******按下任意键返回主菜单******" << endl;

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
			main();
		}
		else
		{
			cout << "输入内容无效，请重新输入:";
			goto 确定4;
		}
		cout << endl;
		cout << "******欢迎下次使用******" << endl;
		exit(0);
		break; }
	case 5:
		cout << endl;
		cout << "是否确定退出登录？如果确定，请输入“确定”（否则，输入“取消”）：";
		string decide;
		确定:
		getline(cin, decide);
		if (decide == "确定")
		{
			cout << endl;
			cout << "正在退出......" << endl;
			is_log = false;
			main();
		}
		else if (decide == "取消")
		{
			cout << endl;
			cout << "******已取消******" << endl;
			cout << endl;
			cout << "******按下任意键返回主菜单******" << endl;

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
			main();
		}
		else
		{
			cout << "输入内容无效，请重新输入:";
			goto 确定;
		}
		break;
	}
	/*initial();
	turn("上海", "重庆");
	order_turn(all_turn);*/
}