#include"GameProperties.h"

GameProperties::GameProperties()
{
	NumOfTurn = 0;
}
GameProperties::GameProperties(int IDGame, int SizeBoard, string Player1, string Player2)
{
	this->IDGame = IDGame;
	this->SizeBoard = SizeBoard;
	this->Player1 = Player1;
	this->Player2 = Player2;
	NumOfTurn = 0;
}
GameProperties::~GameProperties()
{
	//
}

void GameProperties::setIDGame(int IDGame)
{
	this->IDGame = IDGame;
}
void GameProperties::setSizeBoard(int SizeBoard)
{
	this->SizeBoard = SizeBoard;
}
void GameProperties::setPlayer1(string Player1)
{
	this->Player1 = Player1;
}
void GameProperties::setPlayer2(string Player2)
{
	this->Player2 = Player2;
}
void GameProperties::setWiner(string Winer)
{
	this->Winer = Winer;
}

void GameProperties::initializeDefaultBoard(int SizeBoard)
{
	vector<vector<char>> DefaultBoard(SizeBoard, vector<char>(SizeBoard, ' '));
	PointOfBoard = DefaultBoard;
}
void GameProperties::addCheckedPoint(int Row, int Col, char Checked)
{
	PointOfBoard[Row][Col] = Checked;
	NumOfTurn++;
}
void GameProperties::addRecordPoint(shared_ptr<PointChecked> CheckedRecord)
{
	PointRecord.push_back(CheckedRecord);
}

int GameProperties::getIDGame()
{
	return IDGame;
}
int GameProperties::getSizeBoard()
{
	return SizeBoard;
}
int GameProperties::getNumOfTurn()
{
	return NumOfTurn;
}
string GameProperties::getPlayer1()
{
	return Player1;
}
string GameProperties::getPlayer2()
{
	return Player2;
}
string GameProperties::getWiner()
{
	return Winer;
}
vector<vector<char>> GameProperties::getPointOfBoard()
{
	return PointOfBoard;
}
vector<shared_ptr<PointChecked>> GameProperties::getPointRecord()
{
	return PointRecord;
}