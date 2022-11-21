#include"GameRecord.h"

GameRecord::GameRecord()
{
	//
}
GameRecord::GameRecord(int ID, int SizeBoard, string Player1, string Player2, string Winer, vector<shared_ptr<PointChecked>> PointRecord)
{
	this->ID = ID;
	this->SizeBoard = SizeBoard;
	this->Player1 = Player1;
	this->Player2 = Player2;
	this->Winer = Winer;
	this->PointRecord = PointRecord;
}
GameRecord::~GameRecord()
{
	//
}

void GameRecord::setID(int ID)
{
	this->ID = ID;
}
void GameRecord::setSizeBoard(int SizeBoard)
{
	this->SizeBoard = SizeBoard;
}
void GameRecord::setPlayer1(string Player1)
{
	this->Player1 = Player1;
}
void GameRecord::setPlayer2(string Player2)
{
	this->Player2 = Player2;
}
void GameRecord::setWiner(string Winer)
{
	this->Winer = Winer;
}
void GameRecord::setPointRecord(vector<shared_ptr<PointChecked>> PointRecord)
{
	this->PointRecord = PointRecord;
}

int GameRecord::getID()
{
	return ID;
}
int GameRecord::getSizeBoard()
{
	return SizeBoard;
}
string GameRecord::getPlayer1()
{
	return Player1;
}
string GameRecord::getPlayer2()
{
	return Player2;
}
string GameRecord::getWiner()
{
	return Winer;
}
vector<shared_ptr<PointChecked>> GameRecord::getPointRecord()
{
	return PointRecord;
}