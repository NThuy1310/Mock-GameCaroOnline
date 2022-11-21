#pragma once
#include<string>

using namespace std;

class Player
{
private:
	string Name;
	int NumWin = 0;
	int NumLose = 0;
	int NumDraw = 0;
public:
	Player();
	Player(string);
	Player(string, int, int, int);
	~Player();
	//Setter
	void setName(string);
	void setWin(int);
	void setLose(int);
	void setDraw(int);
	//Getter
	string getName();
	int getWin();
	int getLose();
	int getDraw();
	//Get rank of player
	int getRank();
};