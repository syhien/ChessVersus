#pragma once
#include <vector>
#include <ctime>
using namespace std;

struct Status
{
	tm  time;
	int game_id;
	int player1_id;
	int player2_id;
	vector< vector<char> > status;
	int next_player;
};