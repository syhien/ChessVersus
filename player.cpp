#include "player.h"
#include <algorithm>

bool Player::PlayerExist(int id)
{
	for (auto i : all_player_)
		if (i.id_ == id)
			return true;
	return false;
}

bool Player::PlayerExist(string name)
{
	for (auto i : all_player_)
		if (i.name_ == name)
			return true;
	return false;
}

string Player::GetName(int id)
{
	string name = "";
	for (auto i : all_player_)
		if (i.id_ == id)
			name = i.name_;
	return name;
}

int Player::GetId(string name)
{
	int id = -1;
	for (auto i : all_player_)
		if (i.name_ == name)
			id = i.id_;
	return id;
}

bool Player::PlayerLogin(string name, string password)
{
	for (auto i : all_player_)
		if (i.name_ == name)
			if (i.password_ == password)
				return true;
			else
				return false;
	return false;
}

void Player::PlayerChangePassword(int id, string new_password)
{
	for (auto i : all_player_)
		if (i.id_ == id)
			i.password_ = new_password;
}

void Player::AddPlayer(int id, string name, string password)
{
	all_player_.push_back({ id,name,password });
}

void Player::AddPlayer(PlayerInfo player)
{
	all_player_.push_back(player);
}

int Player::Size()
{
	return all_player_.size();
}

bool Player::DeletePlayer(int id)
{
	if (!PlayerExist(id))
		return 0;
	for (auto i = all_player_.begin(); i != all_player_.end(); i++)
		if (i->id_ == id)
		{
			all_player_.erase(i);
			return 1;
		}
}