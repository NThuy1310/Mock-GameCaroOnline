#pragma once
#include<tchar.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"IO.h"
#include"ConsoleSetting.h"


#define MAX_BUFFER_SIZE 4096

using namespace std;

enum StatusCode
{
	NONE_PLAYER = 0,
	LOG_IN = 1,
	REGISTER = 2,
	ACCOUT_EXISTED = 3,
	ACCOUT_NOT_EXISTED = 4,
	ACCPETED = 5,
	FIND_INFO = 6,
	FIND_GAME = 7,
	NEW_GAME = 8,
	IN_GAME = 9,
	WIN = 10,
	LOSE = 11,
	DRAW1 = 12,
	DRAW2 = 13,
	YOUR_POINT = 14,
	OPPONENT_POINT = 15,
	LIST_REPLAY = 16,
	REPLAY_GAME = 17,
	RESEND = 18
};
enum MenuFunction
{
	PLAYER_INFO = 1,
	PLAY_GAME = 2,
	LIST_GAME_PLAYED = 3,
	GAME_PLAYED = 4,
	EXIT_FUNCTION = 5
};

class Client
{
private:
	string IPAdress;
	string Port;
	bool run = true;
	
public:
	Client();
	~Client();

	// Config
	bool setupDLL();
	SOCKET createSocket();
	void connectToServer();

	//
	int sendMsg(SOCKET, string);
	vector<string> getDataMsg(string);
	//Function
	void loginToServer(SOCKET);
	void registerToServer(SOCKET);

	void menu(SOCKET, string);
	void findInfo(SOCKET, string);
	void playGame(SOCKET, string);
	void inGame(SOCKET, string);
	void changeTurn(char&);
	void findListGame(SOCKET, string);
	void replayGame(SOCKET, string);
};