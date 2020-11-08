#include "player.h"
#include "record.h"
#include "status.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
using namespace std;

const string ask_for_check = "（按y确认，按其他按键取消）\n";
const string kick_to_continue = "按任意按键继续\n";

Player player;
vector <Record> record;

string admin_password;

void GameInitialize();
void Login();
void AdminPanel();

int main()
{
	system("cls");
	srand(time(0));
	GameInitialize();
	Login();

	cout << "\nUnfinished project\n";
	return 0;
}

void GameInitialize()
{
	ifstream fin;
	fin.open("game.data");
	if (!fin)
		fin.open("game_template.data");
	if (!fin)//全新初始化
	{
		cout << "输入新管理员密码:\n（空格及之后的内容会被忽略）";
		cin >> admin_password;
		fflush(stdin);
		cout << "新管理员密码为：" << admin_password << endl;
		cout << kick_to_continue, _getch();
	}
	else//有配置
	{
		fin >> admin_password;

	}
	fin.close();
}

void Login()
{

}

void AdminPanel()
{

}
