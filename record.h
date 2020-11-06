#pragma once
#include <ctime>
#include <string>

struct Record
{
	tm time;
	int game_id;
	int player1_id;
	int player2_id;
	int winner;
};