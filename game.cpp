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
	cout << "下面为玩家们说明翻转棋的游戏规则\n1.在8X8的棋盘上交替下子\n2.游戏起始时，棋盘正中央交替地预置了 + - 两棋各2个棋子\n3.把自己颜色的棋子放在棋盘的空格上，而当自己放下的棋子在横、竖、斜八个方向内有一个自己的棋子且两棋子的连线上有且只有对方的棋子，则被夹在中间的全部翻转会成为自己的棋子。并且，只有在可以翻转棋子的地方才可以下子\n4.无法下子时，只能放弃此回合\n";
	cout << "\n玩家1使用wasd控制光标上左下右移动选择落棋点，使用空格确认落棋，用 + 代表玩家1的棋子\n";
	cout << "\n玩家2使用方向键控制光标上下左右移动选择落棋点，使用回车确认落棋，用 - 代表玩家2的棋子\n";
	cout << "\n游戏中的任意时候都可以按下ESC中断游戏\n";
	bool player_turn = status.player_turn;
	bool game_exit = 0;
	while (!game_exit or (!ReversiCan1(status.status) and !ReversiCan2(status.status)) and ChessCount(status.status, '+') and ChessCount(status.status, '-'))
	{
		cout << "接下来是玩家" << (!player_turn ? "1" : "2") << "的回合，按任意键继续\n", _getch();
		if (!player_turn)//p1
		{
			if (!ReversiCan1(status.status))
			{
				cout << "玩家1没有合法的落棋点，按任意键放弃本次落棋\n", _getch();
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
						cout << "这里不能落棋\n请重新选择\n", _getch();
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
				cout << "玩家2没有合法的落棋点，按任意键放弃本次落棋\n", _getch();
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
						cout << "这里不能落棋\n请重新选择\n", _getch();
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
		cout << "是否保存棋局，按y确认保存，按其他按键不进行保存\n";
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
			cout << "玩家2被翻转所有棋子\n";
			status.record.winner = 1;
		}
		else if (!ChessCount(status.status, '+'))
		{
			cout << "玩家1被翻转所有棋子\n";
			status.record.winner = 2;
		}
		else
		{
			if (ChessCount(status.status, '+') == ChessCount(status.status, '-'))
				cout << "双方棋子数相同\n", status.record.winner = 0;
			else
			{
				if (ChessCount(status.status, '+') > ChessCount(status.status, '-'))
					cout << "玩家1棋子数多于玩家2\n", status.record.winner = 1;
				else
					cout << "玩家2棋子数多于玩家1\n", status.record.winner = 2;
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