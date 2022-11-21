#pragma once
#include<string>
#include"PointRecord.h"
#include<vector>
#include<memory>

class GameRecord
{
private:
	int ID;
	int SizeBoard;
	string Player1;
	string Player2;
	string Winer;
	vector<shared_ptr<PointChecked>> PointRecord;
public:
	GameRecord();
	GameRecord(int, int, string, string, string, vector<shared_ptr<PointChecked>>);
	~GameRecord();

	void setID(int);
	void setSizeBoard(int);
	void setPlayer1(string);
	void setPlayer2(string);
	void setWiner(string);
	void setPointRecord(vector<shared_ptr<PointChecked>>);

	int getID();
	int getSizeBoard();
	string getPlayer1();
	string getPlayer2();
	string getWiner();
	vector<shared_ptr<PointChecked>> getPointRecord();
};