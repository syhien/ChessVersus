#include "player.h"
#include "record.h"
#include "status.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

const string ask_for_check = "����yȷ�ϣ�����������ȡ����\n";
const string kick_to_continue = "�����ⰴ������\n";

Player player;
vector <Record> record;

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

	}
	else//������
	{

	}
}

void Login()
{

}

void AdminPanel()
{

}
