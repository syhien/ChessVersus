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

const string ask_for_check = "����yȷ�ϣ�����������ȡ����\n";
const string kick_to_continue = "�����ⰴ������\n";

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
		cout << "��ǰ��¼�û���" << player.GetName(player1_id) << endl << "��ǰ��¼�û���" << player.GetName(player2_id) << endl;
		cout << "ϣ����Щʲô�أ����²���ǰ��Ӧ�ļ��̰�����\n1.��ʼ����Ϸ\n2.�鿴��Ϸ��¼\nESC.�˳���Ϸ\n";
		char ch = _getch();
		char game_choose;
		Record new_record;
		Status new_status;

		switch (ch)
		{
		case '1':
			cout << "��ѡ����Ҫ���е���Ϸ��\n1.��ת��\n2.������\n3.������\n";
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
						cout << "ƽ�֣�˫�������Ժ�\n" << kick_to_continue, _getch();
					else
						cout << "��ϲ" << player.GetName(new_record.winner == 1 ? player1_id : player2_id) << "��ʤ\n" << kick_to_continue, _getch();
				}
				break;
			case '2':

				break;
			case '3':

				break;
			default:
				cout << "�������˳��������İ�����\n" << kick_to_continue, _getch();
				break;
			}
			break;
		case '2':
			for (auto i : record)
				if ((i.player1_id == player1_id and i.player2_id == player2_id) or (i.player1_id == player2_id and i.player2_id == player1_id))
				{
					cout << "��Ϸ���ͣ�" << (i.game_id == 1 ? "��ת��" : (i.game_id == 2 ? "������" : "������")) << endl;
					cout << "UTC +0 ��Ϸʱ�䣺" << asctime(&i.time);
					cout << "���1��" << player.GetName(i.player1_id) << " ���2��" << player.GetName(i.player2_id) << endl;
					cout << "��ʤ�����" << (i.winner == 0 ? "ƽ��" : (i.winner == 1 ? "���1��ʤ" : "���2��ʤ")) << endl;
					cout << endl << endl;
				}
			cout << kick_to_continue, _getch();
			break;
		case 27:
			cout << "�˳���Ϸ\n";
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
	if (!fin)//ȫ�³�ʼ��
	{
		cout << "�����¹���Ա����:\n���ո�֮������ݻᱻ���ԣ�";
		cin >> admin_password;
		fflush(stdin);
		cout << "�¹���Ա����Ϊ��" << admin_password << endl;
		cout << kick_to_continue, _getch();
	}
	else//������
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
		cout << "��ǰ�ѵ�¼" << num_of_login_player << "λ���\n";
		if (num_of_login_player == 1)
			cout << "Player 1: " << player.GetName(player1_id) << " �ѵ�¼\n����Ҫ��¼1λ���\n";
		cout << "������Ӧ����ִ�в���:\n1.�û���¼\n2.�û�ע��\nESC.�˳���¼\n";
		char ch;
		PlayerInfo new_player;
		string login_user_name;
		string login_user_password;
		string login_admin_password;
		ch = _getch();
		switch (ch)
		{
		case '1':
			cout << "����������ǳƣ�\n";
			cin >> login_user_name;
			if (login_user_name == "admin" or login_user_name == "Admin")
			{
				cout << "�������Ա��������֤���:\n";
				cin >> login_admin_password;
				if (login_admin_password == admin_password)
					AdminPanel();
				else
					cout << "����Ա�������\n" << kick_to_continue, _getch();
				break;
			}
			if (!player.PlayerExist(login_user_name))
			{
				cout << "������ϵͳ���������ǳ�Ϊ" << login_user_name << "���û�\n��Ҫע��һ���ǳ�Ϊ" << login_user_name << "���û���\n" << ask_for_check;
				if (_getch() == 'y')
				{
					new_player.id_ = rand() % 100000;
					while (player.GetName(new_player.id_) != "")
						new_player.id_ = rand() % 100000;
					new_player.name_ = login_user_name;
					cout << "��������û����룬�벻Ҫʹ�ÿո�:\n";
					cin >> new_player.password_;
					player.AddPlayer(new_player);
					cout << "ע��ɹ��������µ�¼\n" << kick_to_continue;
					_getch();
					break;
				}
				else
				{
					cout << "����ע��\n" << kick_to_continue, _getch();
					break;
				}
			}
			cout << "����������:\n";
			cin >> login_user_password;
			if (player.PlayerLogin(login_user_name,login_user_password))
			{
				cout << "��¼�ɹ�\n" << kick_to_continue, _getch();
				num_of_login_player++;
				if (num_of_login_player == 1)
					player1_id = player.GetId(login_user_name);
				else
					player2_id = player.GetId(login_user_name);
				break;
			}
			else
			{
				cout << "��¼ʧ��\n" << kick_to_continue;
				_getch();
				break;
			}
			break;
		case '2':
			cout << "����������ǳƣ�\n";
			cin >> login_user_name;
			new_player.id_ = rand() % 100000;
			while (player.GetName(new_player.id_) != "")
				new_player.id_ = rand() % 100000;
			new_player.name_ = login_user_name;
			cout << "��������û����룬�벻Ҫʹ�ÿո�:\n";
			cin >> new_player.password_;
			player.AddPlayer(new_player);
			cout << "ע��ɹ��������µ�¼\n" << kick_to_continue;
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
		cout << "����Ա����:\n1.�鿴�����û�\n2.�����û�\n3.�޸��û���Ϣ\n4.ɾ���û�\n5.�޸Ĺ���Ա����\n6.�鿴������Ϸ��¼\n7.ɾ��ָ����Ϸ��¼\n0.�˳�\n";
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
			cout << "�������û��ǳƣ������ո񣩺����루�����ո񣩣��ÿո���зָ�:\n";
			new_player.id_ = rand() % 100000;
			while (player.PlayerExist(new_player.id_))
				new_player.id_ = rand() % 100000;
			cin >> new_player.name_ >> new_player.password_;
			player.AddPlayer(new_player);
			cout << "������\n" << kick_to_continue;
			_getch();
			break;
		case 3:
			for (auto i : player.all_player_)
				cout << "id:" << i.id_ << " name:" << i.name_ << " password:" << i.password_ << endl;
			cout << kick_to_continue, _getch();
			cout << "������༭�µ��û���id\n";
			cin >> edit_player_id;
			if(!player.PlayerExist(edit_player_id))
			{
				cout << "ָ��id�û�������\n" << kick_to_continue;
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
			cout << "�Ƿ��޸��ǳƣ����û�ԭ�ǳ�Ϊ:" << new_player.name_ << endl << ask_for_check;
			if (_getch() == 'y')
			{
				cout << "���������ǳ�:\n";
				cin >> new_player.name_;
			}
			cout << "�Ƿ��޸����룿���û�ԭ����Ϊ:" << new_player.password_ << endl << ask_for_check;
			if (_getch() == 'y')
			{
				cout << "������������:\n";
				cin >> new_player.password_;
			}
			player.AddPlayer(new_player);
			cout << "�޸����\n" << kick_to_continue;
			_getch();
			break;
		case 4:
			for (auto i : player.all_player_)
				cout << "id:" << i.id_ << " name:" << i.name_ << " password:" << i.password_ << endl;
			cout << "�����ɾ���û�id\n";
			cin >> edit_player_id;
			if(!player.PlayerExist(edit_player_id))
			{
				cout << "�û������ڣ�ɾ��ʧ��\n" << kick_to_continue;
				_getch();
			}
			else
			{
				player.DeletePlayer(edit_player_id);
				cout << "ɾ���ɹ�\n" << kick_to_continue;
				_getch();
			}
			break;
		case 5:
			cout << "�������µĹ���Ա���룺\n";
			cin >> admin_password;
			cout << "�¹���Ա����Ϊ��" << admin_password << endl;
			cout << kick_to_continue, _getch();
			break;
		case 6:
			for (auto i : record)
			{
				cout << "��Ϸ���ͣ�" << (i.game_id == 1 ? "��ת��" : (i.game_id == 2 ? "������" : "������")) << endl;
				cout << "UTC +0 ��Ϸʱ�䣺" << asctime(&i.time);
				cout << "���1��" << player.GetName(i.player1_id) << " ���2��" << player.GetName(i.player2_id) << endl;
				cout << "��ʤ�����" << (i.winner == 0 ? "ƽ��" : (i.winner == 1 ? "���1��ʤ" : "���2��ʤ")) << endl;
				cout << endl << endl;
			}
			cout << kick_to_continue, _getch();
			break;
		case 7:
			record_count = 0;
			for (auto i : record)
			{
				cout << "<" << record_count++ << ">" << endl;
				cout << "��Ϸ���ͣ�" << (i.game_id == 1 ? "��ת��" : (i.game_id == 2 ? "������" : "������")) << endl;
				cout << "UTC +0 ��Ϸʱ�䣺" << asctime(&i.time);
				cout << "���1��" << player.GetName(i.player1_id) << " ���2��" << player.GetName(i.player2_id) << endl;
				cout << "��ʤ�����" << (i.winner == 0 ? "ƽ��" : (i.winner == 1 ? "���1��ʤ" : "���2��ʤ")) << endl;
				cout << endl << endl;
			}
			cout << "��������Ҫɾ���ļ�¼��ĳ����¼�������ڵ����֣�������ɾ��������-1\n";
			cin >> record_count;
			if (record_count == -1)
			{
				cout << "ɾ��ʧ��\n" << kick_to_continue, _getch();
				break;
			}
			record.erase(record.begin() + record_count);
			cout << "ɾ���ɹ�\n" << kick_to_continue, _getch();
			break;
		case 0:
			cout << "�˳�����Ա���\n" << kick_to_continue, _getch();
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