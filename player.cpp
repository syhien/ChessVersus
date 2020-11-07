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
	string name;
	for (auto i : all_player_)
		if (i.id_ == id)
			name = i.name_;
	return name;
}

int Player::GetId(string name)
{
	int id;
	for (auto i : all_player_)
		if (i.name_ == name)
			id = i.id_;
	return id;
}

bool Player::PlayerLogin(int id, string password)
{
	for (auto i : all_player_)
		if (i.id_ == id)
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
