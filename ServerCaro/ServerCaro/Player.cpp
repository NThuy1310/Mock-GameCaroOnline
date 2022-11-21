#include"Player.h"

Player::Player()
{
	//
}
Player::Player(string Name)
{
	this->Name = Name;
	NumWin = 0;
	NumDraw = 0;
	NumLose = 0;
}
Player::Player(string Name, int NumWin, int NumDraw, int NumLose)
{
	this->Name = Name;
	this->NumWin = NumWin;
	this->NumDraw = NumDraw;
	this->NumLose = NumLose;
}
Player::~Player()
{
	//
}

void Player::setName(string Name)
{
	this->Name = Name;
}
void Player::setWin(int NumWin)
{
	this->NumWin = NumWin;
}
void Player::setLose(int NumLose)
{
	this->NumLose = NumLose;
}
void Player::setDraw(int NumDraw)
{
	this->NumDraw = NumDraw;
}

string Player::getName()
{
	return Name;
}
int Player::getWin()
{
	return NumWin;
}
int Player::getLose()
{
	return NumLose;
}
int Player::getDraw()
{
	return NumDraw;
}
int Player::getRank()
{
	// Rank conversion
	int FWin = 3;
	int FDraw = 1;
	int FLose = 0;
	int PlayerRank = NumWin * FWin + NumDraw * FDraw + NumLose * FLose;
	return PlayerRank;
}