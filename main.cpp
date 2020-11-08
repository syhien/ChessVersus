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
		int num_of_player;
		fin >> num_of_player;
		for (int i = 0; i < num_of_player; i++)
		{
			int id;
			string name;
			string password;
			fin >> id >> name >> password;
			player.AddPlayer(id, name, password);
		}
		int num_of_records;
		fin >> num_of_records;
		for (int i = 0; i < num_of_records; i++)
		{
			Record new_record;
			fin >> new_record.time.tm_sec >> new_record.time.tm_min >> new_record.time.tm_hour >> new_record.time.tm_mday >> new_record.time.tm_mon >> new_record.time.tm_year >> new_record.time.tm_wday >> new_record.time.tm_yday >> new_record.time.tm_isdst >> new_record.game_id >> new_record.player1_id >> new_record.player2_id >> new_record.winner;
			record.push_back(new_record);
		}
	}
	fin.close();
}

void Login()
{

}

void AdminPanel()
{

}
