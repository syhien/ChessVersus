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
int player1_id;
int player2_id;

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
	int num_of_login_player = 0;
	bool login_exit = 0;
	while (!login_exit and num_of_login_player < 2)
	{
		system("cls");
		cout << "当前已登录" << num_of_login_player << "位玩家\n";
		if (num_of_login_player == 1)
			cout << "Player 1: " << player.GetName(player1_id) << " 已登录\n还需要登录1位玩家\n";
		cout << "按下相应按键执行操作:\n1.用户登录\n2.用户注册\nESC.退出程序\n";
		char ch;
		PlayerInfo new_player;
		string login_user_name;
		string login_user_password;
		string login_admin_password;
		ch = _getch();
		switch (ch)
		{
		case '1':
			cout << "请输入你的昵称：\n";
			cin >> login_user_name;
			if (login_user_name == "admin" or login_user_name == "Admin")
			{
				cout << "输入管理员密码以验证身份:\n";
				cin >> login_admin_password;
				if (login_admin_password == admin_password)
					AdminPanel();
				else
				{
					cout << "管理员密码错误\n" << kick_to_continue, _getch();
					break;
				}
			}
			if (!player.PlayerExist(login_user_name))
			{
				cout << "看起来系统并不存在昵称为" << login_user_name << "的用户\n需要注册一个昵称为" << login_user_name << "的用户吗？\n" << ask_for_check;
				if (_getch() == 'y')
				{
					new_player.id_ = rand() % 100000;
					while (player.GetName(new_player.id_) != "")
						new_player.id_ = rand() % 100000;
					new_player.name_ = login_user_name;
					cout << "输入你的用户密码，请不要使用空格:\n";
					cin >> new_player.password_;
					player.AddPlayer(new_player);
					cout << "注册成功，请重新登录\n" << kick_to_continue;
					_getch();
					break;
				}
				else
				{
					cout << "放弃注册\n" << kick_to_continue, _getch();
					break;
				}
			}
			cout << "请输入密码:\n";
			cin >> login_user_password;
			if (player.PlayerLogin(login_user_name,login_user_password))
			{
				cout << "登录成功\n" << kick_to_continue, _getch();
				num_of_login_player++;
				if (num_of_login_player == 1)
					player1_id = player.GetId(login_user_name);
				else
					player2_id = player.GetId(login_user_name);
				break;
			}
			else
			{
				cout << "登录失败\n" << kick_to_continue;
				_getch();
				break;
			}
			break;
		case 27:
			login_exit = 1;
			break;
		default:
			break;
		}
	}
}

void AdminPanel()
{

}
