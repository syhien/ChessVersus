#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

void DrawConsole(char chess[8][8], pair <int, int> current_positon)
{
	system("cls");
	string graph = "";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (make_pair(i, k) == current_positon)
				{
					switch (j)
					{
					case 0:
						graph += "*****";
						break;
					case 1:
						graph += "* ";
						graph += chess[i][k];
						graph += " *";
						break;
					case 2:
						graph += "*****";
						break;
					default:
						break;
					}
				}
				else if (chess[i][k] != ' ')
				{
					switch (j)
					{
					case 1:
						graph += "| ";
						graph += chess[i][k];
						graph += " |";
						break;
					default:
						graph += "-----";
						break;
					}
				}
				else
				{
					switch (j)
					{
					case 1:
						graph += "|   |";
						break;
					default:
						graph += "-----";
						break;
					}
				}
			}
			graph += "\n";
		}
	}
	cout << graph;
}