#pragma once
#include"Player.h"
#include"GameProperties.h"
#include"GameRecord.h"
#include<map>
#include<memory>
#include<fstream>
#include<sstream>
#include<algorithm>

class Database
{
public:
	// 3 type of file
	// 1. AllPlayerInfo.ini
	// 2. PlayerInfo.ini
	// 3. IDGame.ini

	//find username in Databases return TRUE if player name is existed
	static bool checkExistName(string);
	// add or update player to database
	static void addPlayer(shared_ptr<Player>);
	// Return a map ListPlayer from databases
	static map<string, shared_ptr<Player>> getListPlayer();
	// Return a shared pointer of class Player
	static shared_ptr<Player> findPlayer(string);
	static shared_ptr<Player> getSuitablePlayer(string, vector<string>);

	// Write or update info of a played game to 2 player file
	static void recordToPlayerFile(shared_ptr<GameProperties>);

	// Get list information of played game
	static map<int, shared_ptr<GameRecord>> getListGamePlayed(string);


	// File json
	// Convert json object to shared pointer of class Player
	//static void from_json(json&, shared_ptr<Player>);
	static string convertPlayertoData(shared_ptr<Player>);
	static shared_ptr<Player> convertDatatoPlayer(string);
	static vector<string> getDataFromString(string);

	// Save ID Game to database
	static void writeIDFile(int);
	static int getPreIDGame();
};