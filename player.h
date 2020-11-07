#pragma once
#include <string>
#include <vector>
using namespace std;

struct PlayerInfo
{
	int id_;
	string name_;
	string password_;
};

class Player
{
public:

private:
	vector <PlayerInfo> all_player;
};