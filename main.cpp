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

	}
	fin.close();
}

void Login()
{

}

void AdminPanel()
{

}
