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

bool status_exist;

void GameInitialize();
void Login();
void AdminPanel();
void GameSafe();
void GameSafeWithStatus();
void DrawConsole(char chess[8][8], pair<int, int> current_positon);
void GraphTest();
Record NewReversi(int player1_id, int player2_id, Status& status);
Record NewGomoku(int player1_id, int player2_id, Status& status);
Record NewMoves(int player1_id, int player2_id, Status& status);

int main()
{
	system("cls");
	srand(time(0));
	GameInitialize();
	Login();

	bool game_exit = 0;
	while (!game_exit)
	{
		fflush(stdin);
		system("cls");
		cout << "当前登录用户：" << player.GetName(player1_id) << endl << "当前登录用户：" << player.GetName(player2_id) << endl;
		cout << "希望做些什么呢？按下操作前对应的键盘按键吧\n1.开始新游戏\n2.查看游戏记录\nESC.退出游戏\n";
		char ch = _getch();
		char game_choose;
		Record new_record;
		Status new_status;

		switch (ch)
		{
		case '1':
			cout << "请选择想要进行的游戏：\n1.翻转棋\n2.五子棋\n3.移子棋\n";
			game_choose = _getch();
			switch (game_choose)
			{
			case '1':
				new_record = NewReversi(player1_id, player2_id, new_status);
				if (new_record.winner == -1)
				{

				}
				else
				{
					record.push_back(new_record);
					if (!new_record.winner)
						cout << "平局！双方握手言和\n" << kick_to_continue, _getch();
					else
						cout << "恭喜" << player.GetName(new_record.winner == 1 ? player1_id : player2_id) << "获胜\n" << kick_to_continue, _getch();
				}
				break;
			case '2':

				break;
			case '3':

				break;
			default:
				cout << "好像按下了程序不能理解的按键呢\n" << kick_to_continue, _getch();
				break;
			}
			break;
		case '2':
			for (auto i : record)
				if ((i.player1_id == player1_id and i.player2_id == player2_id) or (i.player1_id == player2_id and i.player2_id == player1_id))
				{
					cout << "游戏类型：" << (i.game_id == 1 ? "翻转棋" : (i.game_id == 2 ? "五子棋" : "移子棋")) << endl;
					cout << "UTC +0 游戏时间：" << asctime(&i.time);
					cout << "玩家1：" << player.GetName(i.player1_id) << " 玩家2：" << player.GetName(i.player2_id) << endl;
					cout << "获胜情况：" << (i.winner == 0 ? "平局" : (i.winner == 1 ? "玩家1获胜" : "玩家2获胜")) << endl;
					cout << endl << endl;
				}
			cout << kick_to_continue, _getch();
			break;
		case 27:
			cout << "退出游戏\n";
			game_exit = 1;
			cout << kick_to_continue, _getch();
			break;
		default:
			break;
		}
	}

	GameSafe();
	//GameSafeWithStatus();

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
		int status_exist_int;
		fin >> status_exist_int;
		status_exist = status_exist_int ? true : false;
		if (status_exist)
		{
			//
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
		cout << "按下相应按键执行操作:\n1.用户登录\n2.用户注册\nESC.退出登录\n";
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
					cout << "管理员密码错误\n" << kick_to_continue, _getch();
				break;
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
		case '2':
			cout << "请输入你的昵称：\n";
			cin >> login_user_name;
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
	bool admin_logout = 0;
	while (!admin_logout)
	{
		system("cls");
		cout << "管理员操作:\n1.查看所有用户\n2.新增用户\n3.修改用户信息\n4.删除用户\n5.修改管理员密码\n6.查看所有游戏记录\n7.删除指定游戏记录\n0.退出\n";
		int ch;
		cin >> ch;
		PlayerInfo new_player;
		int edit_player_id;
		int record_count;
		switch (ch)
		{
		case 1:
			for (auto i : player.all_player_)
				cout << "id:" << i.id_ << " name:" << i.name_ << " password:" << i.password_ << endl;
			cout << kick_to_continue, _getch();
			break;
		case 2:
			cout << "输入新用户昵称（不含空格）和密码（不含空格），用空格或换行分割:\n";
			new_player.id_ = rand() % 100000;
			while (player.PlayerExist(new_player.id_))
				new_player.id_ = rand() % 100000;
			cin >> new_player.name_ >> new_player.password_;
			player.AddPlayer(new_player);
			cout << "添加完成\n" << kick_to_continue;
			_getch();
			break;
		case 3:
			for (auto i : player.all_player_)
				cout << "id:" << i.id_ << " name:" << i.name_ << " password:" << i.password_ << endl;
			cout << kick_to_continue, _getch();
			cout << "输入待编辑新的用户的id\n";
			cin >> edit_player_id;
			if(!player.PlayerExist(edit_player_id))
			{
				cout << "指定id用户不存在\n" << kick_to_continue;
				_getch();
				break;
			}
			for (auto i : player.all_player_)
				if (i.id_ == edit_player_id)
				{
					new_player = i;
					break;
				}
			player.DeletePlayer(edit_player_id);
			cout << "是否修改昵称？该用户原昵称为:" << new_player.name_ << endl << ask_for_check;
			if (_getch() == 'y')
			{
				cout << "输入其新昵称:\n";
				cin >> new_player.name_;
			}
			cout << "是否修改密码？该用户原密码为:" << new_player.password_ << endl << ask_for_check;
			if (_getch() == 'y')
			{
				cout << "输入其新密码:\n";
				cin >> new_player.password_;
			}
			player.AddPlayer(new_player);
			cout << "修改完成\n" << kick_to_continue;
			_getch();
			break;
		case 4:
			for (auto i : player.all_player_)
				cout << "id:" << i.id_ << " name:" << i.name_ << " password:" << i.password_ << endl;
			cout << "输入待删除用户id\n";
			cin >> edit_player_id;
			if(!player.PlayerExist(edit_player_id))
			{
				cout << "用户不存在，删除失败\n" << kick_to_continue;
				_getch();
			}
			else
			{
				player.DeletePlayer(edit_player_id);
				cout << "删除成功\n" << kick_to_continue;
				_getch();
			}
			break;
		case 5:
			cout << "请输入新的管理员密码：\n";
			cin >> admin_password;
			cout << "新管理员密码为：" << admin_password << endl;
			cout << kick_to_continue, _getch();
			break;
		case 6:
			for (auto i : record)
			{
				cout << "游戏类型：" << (i.game_id == 1 ? "翻转棋" : (i.game_id == 2 ? "五子棋" : "移子棋")) << endl;
				cout << "UTC +0 游戏时间：" << asctime(&i.time);
				cout << "玩家1：" << player.GetName(i.player1_id) << " 玩家2：" << player.GetName(i.player2_id) << endl;
				cout << "获胜情况：" << (i.winner == 0 ? "平局" : (i.winner == 1 ? "玩家1获胜" : "玩家2获胜")) << endl;
				cout << endl << endl;
			}
			cout << kick_to_continue, _getch();
			break;
		case 7:
			record_count = 0;
			for (auto i : record)
			{
				cout << "<" << record_count++ << ">" << endl;
				cout << "游戏类型：" << (i.game_id == 1 ? "翻转棋" : (i.game_id == 2 ? "五子棋" : "移子棋")) << endl;
				cout << "UTC +0 游戏时间：" << asctime(&i.time);
				cout << "玩家1：" << player.GetName(i.player1_id) << " 玩家2：" << player.GetName(i.player2_id) << endl;
				cout << "获胜情况：" << (i.winner == 0 ? "平局" : (i.winner == 1 ? "玩家1获胜" : "玩家2获胜")) << endl;
				cout << endl << endl;
			}
			cout << "请输入想要删除的记录的某条记录尖括号内的数字，不进行删除请输入-1\n";
			cin >> record_count;
			if (record_count == -1)
			{
				cout << "删除失败\n" << kick_to_continue, _getch();
				break;
			}
			record.erase(record.begin() + record_count);
			cout << "删除成功\n" << kick_to_continue, _getch();
			break;
		case 0:
			cout << "退出管理员面板\n" << kick_to_continue, _getch();
			admin_logout = 1;
			break;
		default:
			break;
		}
	}
}

void GameSafe()
{
	ofstream fout("game.data");
	fout << admin_password << endl;
	fout << player.all_player_.size() << endl;
	for (auto i : player.all_player_)
		fout << i.id_ << " " << i.name_ << " " << i.password_ << endl;
	fout << record.size() << endl;
	for (auto i : record)
		fout << i.time.tm_sec << " " << i.time.tm_min << " " << i.time.tm_hour << " " << i.time.tm_mday << " " << i.time.tm_mon << " " << i.time.tm_year << " " << i.time.tm_wday << " " << i.time.tm_yday << " " << i.time.tm_isdst << " " << i.game_id << " " << i.player1_id << " " << i.player2_id << " " << i.winner << endl;
	fout << "0";
}

void GameSafeWithStatus()
{
	ofstream fout("game.data");
	fout << admin_password << endl;
	fout << player.all_player_.size() << endl;
	for (auto i : player.all_player_)
		fout << i.id_ << " " << i.name_ << " " << i.password_ << endl;
	fout << record.size() << endl;
	for (auto i : record)
		fout << i.time.tm_sec << " " << i.time.tm_min << " " << i.time.tm_hour << " " << i.time.tm_mday << " " << i.time.tm_mon << " " << i.time.tm_year << " " << i.time.tm_wday << " " << i.time.tm_yday << " " << i.time.tm_isdst << " " << i.game_id << " " << i.player1_id << " " << i.player2_id << " " << i.winner << endl;
	fout << "1";
	//
}

void GraphTest()
{
	char chess[8][8] = { {'+','-','+','+',' ','+','+','+'},{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} ,{'+','-','+','+',' ','+','+','+'} };
	DrawConsole(chess, make_pair(3, 2));
}