#include "record.h"
#include "status.h"
#include <ctime>
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
using namespace std;

void DrawConsole(char chess[8][8], pair <int, int> current_positon);

int ChessCount(char chess[8][8], char c)
{
	int count = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (chess[i][j] == c)
				count++;
	return count;
}

bool ReversiLegal(char chess[8][8], pair <int, int> position, char c)
{
	if (chess[position.first][position.second] != ' ')
		return 0;
	//up
	for (int i = position.first - 1, j = position.second, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i--)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//up right
	for (int i = position.first - 1, j = position.second + 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i--, j++)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//right
	for (int i = position.first, j = position.second + 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; j++)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//down right
	for (int i = position.first + 1, j = position.second + 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i++, j++)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//down
	for (int i = position.first + 1, j = position.second, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i++)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//down left
	for (int i = position.first + 1, j = position.second - 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i++, j--)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//left
	for (int i = position.first, j = position.second - 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; j--)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	//up left
	for (int i = position.first - 1, j = position.second - 1, diffrent_count = 0; i >= 0 and i < 8 and j >= 0 and j < 8; i--, j--)
	{
		if (chess[i][j] == c)
		{
			if (diffrent_count)
				return 1;
			else
				break;
		}
		if (chess[i][j] == ' ')
			break;
		diffrent_count++;
	}

	return 0;
}

bool ReversiCan1(char chess[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (chess[i][j] == ' ')
				if (ReversiLegal(chess, make_pair(i, j), '+'))
					return 1;
	return 0;
}

bool ReversiCan2(char chess[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (chess[i][j] == ' ')
				if (ReversiLegal(chess, make_pair(i, j), '-'))
					return 1;
	return 0;
}

void ReversiPut(char chess[8][8], pair <int, int> position, char c)
{
	vector < pair <int, int> > place_to_put;
	place_to_put.push_back(position);
	stack < pair <int, int> > able_to_put;

	//up
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first - 1, j = position.second; i >= 0 and i < 8 and j >= 0 and j < 8; i--)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//up right
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first - 1, j = position.second + 1; i >= 0 and i < 8 and j >= 0 and j < 8; i--, j++)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//right
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first, j = position.second + 1; i >= 0 and i < 8 and j >= 0 and j < 8; j++)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//down right
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first + 1, j = position.second + 1; i >= 0 and i < 8 and j >= 0 and j < 8; i++, j++)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//down
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first + 1, j = position.second; i >= 0 and i < 8 and j >= 0 and j < 8; i++)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//down left
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first + 1, j = position.second - 1; i >= 0 and i < 8 and j >= 0 and j < 8; i++, j--)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//left
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first, j = position.second - 1; i >= 0 and i < 8 and j >= 0 and j < 8; j--)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	//up left
	while (!able_to_put.empty())
		able_to_put.pop();
	for (int i = position.first - 1, j = position.second - 1; i >= 0 and i < 8 and j >= 0 and j < 8; i--, j--)
	{
		if (chess[i][j] == ' ')
			break;
		if (chess[i][j] != c and chess[i][j] != ' ')
			able_to_put.push(make_pair(i, j));
		if (chess[i][j] == c)
		{
			while (!able_to_put.empty())
			{
				place_to_put.push_back(able_to_put.top());
				able_to_put.pop();
			}
			break;
		}
	}

	for (auto i : place_to_put)
		chess[i.first][i.second] = c;
}

Record NewReversi(int player1_id, int player2_id, Status& status)
{
	time_t t = time(0);
	tm* tm_t = gmtime(&t);
	status.record.time = *tm_t;
	status.record.game_id = 1;
	status.record.player1_id = player1_id;
	status.record.player2_id = player2_id;
	status.record.winner = -1;
	cout << "����Ϊ�����˵����ת�����Ϸ����\n1.��8X8�������Ͻ�������\n2.��Ϸ��ʼʱ�����������뽻���Ԥ���� + - �����2������\n3.���Լ���ɫ�����ӷ������̵Ŀո��ϣ������Լ����µ������ںᡢ����б�˸���������һ���Լ��������������ӵ�����������ֻ�жԷ������ӣ��򱻼����м��ȫ����ת���Ϊ�Լ������ӡ����ң�ֻ���ڿ��Է�ת���ӵĵط��ſ�������\n4.�޷�����ʱ��ֻ�ܷ����˻غ�\n";
	cout << "\n���1ʹ��wasd���ƹ�����������ƶ�ѡ������㣬ʹ�ÿո�ȷ�����壬�� + �������1������\n";
	cout << "\n���2ʹ�÷�������ƹ�����������ƶ�ѡ������㣬ʹ�ûس�ȷ�����壬�� - �������2������\n";
	cout << "\n��Ϸ�е�����ʱ�򶼿��԰���ESC�ж���Ϸ\n";
	bool player_turn = status.player_turn;
	bool game_exit = 0;
	while (!game_exit or (!ReversiCan1(status.status) and !ReversiCan2(status.status)) and ChessCount(status.status, '+') and ChessCount(status.status, '-'))
	{
		cout << "�����������" << (!player_turn ? "1" : "2") << "�Ļغϣ������������\n", _getch();
		if (!player_turn)//p1
		{
			if (!ReversiCan1(status.status))
			{
				cout << "���1û�кϷ�������㣬�������������������\n", _getch();
				continue;
			}
			pair <int, int> position(0, 0);
			bool f = 0;
			while (!f)
			{
				DrawConsole(status.status, position);
				char ch = _getch();
				switch (ch)
				{
				case 'w':
					position.first = (position.first - 1 + 8) % 8;
					break;
				case 'a':
					position.second = (position.second - 1 + 8) % 8;
					break;
				case 's':
					position.first = (position.first + 1 + 8) % 8;
					break;
				case 'd':
					position.second = (position.second + 1 + 8) % 8;
					break;
				case 9://tab
					if (!ReversiLegal(status.status, position, '+'))
					{
						cout << "���ﲻ������\n������ѡ��\n", _getch();
						break;
					}
					ReversiPut(status.status, position, '+');
					f = 1;
					break;
				case 27:
					game_exit = 1;
					f = 1;
					break;
				default:
					break;
				}
			}
		}
		else//p2
		{
			if (!ReversiCan2(status.status))
			{
				cout << "���2û�кϷ�������㣬�������������������\n", _getch();
				continue;
			}
			pair <int, int> position(0, 0);
			bool f = 0;
			while (!f)
			{
				DrawConsole(status.status, position);
				char ch = _getch();
				switch (ch)
				{
				case 'i'://up
					position.first = (position.first - 1 + 8) % 8;
					break;
				case 'j'://left
					position.second = (position.second - 1 + 8) % 8;
					break;
				case 'k'://down
					position.first = (position.first + 1 + 8) % 8;
					break;
				case 'l'://right
					position.second = (position.second + 1 + 8) % 8;
					break;
				case 13://enter
					if (!ReversiLegal(status.status, position, '-'))
					{
						cout << "���ﲻ������\n������ѡ��\n", _getch();
						break;
					}
					ReversiPut(status.status, position, '-');
					f = 1;
					break;
				case 27:
					game_exit = 1;
					f = 1;
					break;
				default:
					break;
				}
			}
		}
		if (!game_exit)
			player_turn = !player_turn;
	}
	if (game_exit)
	{
		status.player_turn = player_turn;
		cout << "�Ƿ񱣴���֣���yȷ�ϱ��棬���������������б���\n";
		if (_getch() == 'y')
		{
			status.record.winner = -1;
		}
		else
		{
			status.record.winner = 2;
		}
	}
	else
	{
		if (!ChessCount(status.status, '-'))
		{
			cout << "���2����ת��������\n";
			status.record.winner = 1;
		}
		else if (!ChessCount(status.status, '+'))
		{
			cout << "���1����ת��������\n";
			status.record.winner = 2;
		}
		else
		{
			if (ChessCount(status.status, '+') == ChessCount(status.status, '-'))
				cout << "˫����������ͬ\n", status.record.winner = 0;
			else
			{
				if (ChessCount(status.status, '+') > ChessCount(status.status, '-'))
					cout << "���1�������������2\n", status.record.winner = 1;
				else
					cout << "���2�������������1\n", status.record.winner = 2;
			}
		}
	}
	return status.record;
}

Record NewGomoku(int player1_id, int player2_id, Status& status)
{
	Record record;
	time_t t = time(0);
	tm* tm_t = gmtime(&t);
	record.time = *tm_t;
	record.game_id = 2;
	record.player1_id = player1_id;
	record.player2_id = player2_id;
	record.winner = -1;
	status.record = record;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			status.status[i][j] = ' ';

	return record;
}

Record NewMoves(int player1_id, int player2_id, Status& status)
{
	Record record;
	time_t t = time(0);
	tm* tm_t = gmtime(&t);
	record.time = *tm_t;
	record.game_id = 3;
	record.player1_id = player1_id;
	record.player2_id = player2_id;
	record.winner = -1;
	status.record = record;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			status.status[i][j] = ' ';

	return record;
}