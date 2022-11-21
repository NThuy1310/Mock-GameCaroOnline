#pragma once
#include"PointRecord.h"
#include"GameRecord.h"
#include<string>
#include<vector>
#include<memory>

using namespace std;

class GameProperties
{
private:
	int IDGame;
	int SizeBoard;
	int NumOfTurn;
	string Player1;
	string Player2;
	string Winer;
	vector<vector<char>> PointOfBoard;
	vector<shared_ptr<PointChecked>> PointRecord;
public:
	GameProperties();
	GameProperties(int, int, string, string);
	~GameProperties();
	//Setter
	void setIDGame(int);
	void setSizeBoard(int);
	void setPlayer1(string);
	void setPlayer2(string);
	void setWiner(string);

	void initializeDefaultBoard(int);
	void addCheckedPoint(int, int, char);
	void addRecordPoint(shared_ptr<PointChecked>);
	//Getter
	int getIDGame();
	int getSizeBoard();
	int getNumOfTurn();
	string getPlayer1();
	string getPlayer2();
	string getWiner();

	vector<vector<char>> getPointOfBoard();
	vector<shared_ptr<PointChecked>> getPointRecord();
};