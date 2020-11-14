#pragma once
#include "record.h"
#include <vector>
#include <ctime>
using namespace std;

struct Status
{
	Record record;
	char status[8][8];
	bool player_turn;
};