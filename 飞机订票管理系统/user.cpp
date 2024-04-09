#include"user.h"
#include"main.h"


extern string user_add;
extern string manager_add;
string log_name;
string log_password;
vector<string> user;
bool is_manager;
bool is_log = false;

bool check(string user_name)
{
	ifstream in;
	string user_information;
	in.open(user_add);
	while (getline(in, user_information))
	{
		string name;
		istringstream information(user_information);
		getline(information, name, ' ');
		if (name == user_name)
		{
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}

bool check_manager(string user_name)
{
	ifstream in;
	string user_information;
	in.open(manager_add);
	while (getline(in, user_information))
	{
		string name;
		istringstream information(user_information);
		getline(information, name, ' ');
		if (name == user_name)
		{
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}

void user_initial(string user_name)
{
	user.clear();
	ifstream in;
	string user_information;
	if (is_manager)
	{
		in.open(manager_add);
	}
	else
	{
		in.open(user_add);
	}
	while (getline(in, user_information))
	{
		string name;
		istringstream information(user_information);
		getline(information, name, ' ');
		if (name == user_name)
		{
			in.close();
			user.push_back(name);
			string more_inf;
			while(getline(information, more_inf, ' '))
			{
				user.push_back(more_inf);
			}
			return;
		}
	}
	
}

void sign()
{
	string name;
	string password;
	string repassword;
	string information;
	cout << endl;
	cout << "******注册******" << endl;
	cout << "请设置用户名：" ;
用户名设置:
	getline(cin, name);
	if (check(name)||check_manager(name))
	{
		cout << "该用户名已经存在，请重新设置：" ;
		goto 用户名设置;
	}


	cout << "请设置密码：" ;
	getline(cin, password);
	cout << "请再次确认密码：";
	
确认密码:
	getline(cin, repassword);
	if (repassword == password)
	{
		information = name + " " + password;
		modify(user_add, name, information);
		cout << "******注册成功******" << endl;
	}
	else
	{
		cout << "两次密码输入不一致，请再次输入：";
		goto 确认密码;
	}
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
}

void log()
{
	bool right = true;
//用户输入:
	cout << endl;
	cout << "******登录******" << endl;
	cout << "请输入用户名：" ;

	getline(cin, log_name);
	is_manager = check_manager(log_name);
	if (!(check(log_name)||is_manager))
	{
		//cout << "不存在该用户，请重新输入:";
		//goto 用户输入;
		right = false;
	}
	else
	{
		user_initial(log_name);
	}
	

	cout << "请输入密码：" ;
//密码输入:
	getline(cin,log_password);
	if ( right == true&&user[1] == log_password)
	{
		if (is_manager)
		{

			cout << endl;
			cout << "******管理员身份已确认******" << endl;
			is_log = true;

		}
		else
		{
			cout << endl;
			cout << "******登陆成功，欢迎******" << endl;
			is_log = true;
		}
		
	}
	else
	{

		cout << endl;
		cout << "******抱歉，登录失败，用户名或密码错误******"<<endl;
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
		cout << endl;
		main();
	}
}