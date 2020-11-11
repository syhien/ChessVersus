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
	bool PlayerExist(int id);
	bool PlayerExist(string name);
	string GetName(int id);
	int GetId(string name);
	bool PlayerLogin(string name, string password);
	void PlayerChangePassword(int id, string new_password);
	void AddPlayer(int id, string name, string password);
	void AddPlayer(PlayerInfo player);
	int Size();
	friend void GameSafe();
	friend void GameSafeWithStatus();
	friend void AdminPanel();
private:
	vector <PlayerInfo> all_player_;
};