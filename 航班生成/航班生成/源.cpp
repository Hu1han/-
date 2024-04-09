#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	vector<string> city;
	ifstream out;
	string s;
	out.open("C://Users//xxx//Desktop//三级项目//城市.txt");
	while (getline(out, s))
	{
		city.push_back(s);
	}
	int city_num = city.size();
	clock_t wait = 1 * CLOCKS_PER_SEC;
	string flight[19] = { "波音737-600","波音737-700ER","波音737-800","波音737-900","波音757-300","波音767-200","波音767-300ER","波音787-800","波音777-200ER","波音777-300","波音747-400","波音747-8I","空客A310","空客A220","空客A320","空客A330","空客A340","空客A350","空客A380" };
	string day[8] = { "周一","周二","周三","周四","周五" ,"周六" ,"周日" ,"周一" };
	for (int i = 0; i <= 20000; i++)
	{
		srand(i);
		char a = rand() % 26 + 65;
		cout << a;
		a = rand() % 26 + 65;
		cout << a;
		a = rand() % 26 + 65;
		cout << a;
		
		int b = rand() % 9 + 1;
		cout << b;
		b = rand() % 9 + 1;
		cout << b;
		b = rand() % 9 + 1;
		cout << b;
		cout << " ";

		int c = rand() % 19;
		cout << flight[c];
		cout << " ";
		
		int d = rand() % city_num;
		cout << city[d];
		cout << " ";

		int e = rand() % city_num;
		while (d == e) 
		{
			e = rand() % city_num;
		}
		cout << city[e];
		cout << " ";

		int f = rand() % 7;
		cout << day[f];
		cout << " ";

		int g = rand() % 2;
		f += g;
		cout << day[f];
		cout << " ";

		int h = rand() % 7;
		cout << h;
		cout << " ";
		
		int l = rand() % 1800 + 700;
		cout << l*6;
		cout << " ";
		
		int j = rand() % 15;
		cout << j;
		cout << " ";

		cout << l * 3;
		cout << " ";

		int k = rand() % 101;
		cout << k;
		cout << " ";
		cout << l << endl;

		/*clock_t start = clock();
		while (clock()-start<wait) 
		{};*/

	}



}
