//#pragma once
//#include"Player.h"
//#include"GameProperties.h"
//#include"GameRecord.h"
//#include<nlohmann/json.hpp>
//#include<map>
//#include<memory>
//#include<fstream>
//#include<algorithm>
//using json = nlohmann::json;
//
//class GameDatabase
//{
//public:
//	// 3 type of file
//	// 1. AllPlayerInfo.json
//	// 2. PlayerInfo.json
//	// 3. IDGame.ini
//
//	//find username in Databases return TRUE if player name is existed
//	static bool checkExistName(string);
//	// add or update player to database
//	static void addPlayer(shared_ptr<Player>);
//	// Return a map ListPlayer from databases
//	static map<string, shared_ptr<Player>> getListPlayer();
//	// Return a shared pointer of class Player
//	static shared_ptr<Player> findPlayer(string);
//	static shared_ptr<Player> getSuitablePlayer(string, vector<string>);
//
//	// Write or update info of a played game to 2 player file
//	static void recordToPlayerFile(shared_ptr<GameProperties>);
//
//	// Get list information of played game
//	static map<string, shared_ptr<GameRecord>> getListGamePlayed(string);
//	
//
//	// File json
//	// Convert json object to shared pointer of class Player
//	static void from_json(json&, shared_ptr<Player>);
//
//	// Save ID Game to database
//	static void writeIDFile(int);
//	static int getPreIDGame();
//};