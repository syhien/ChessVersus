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
	}
	fin.close();
}

void Login()
{

}

void AdminPanel()
{

}
