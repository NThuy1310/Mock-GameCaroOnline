#pragma once
#include<tchar.h>
#include<string>
#include<winsock2.h>
#include<WS2tcpip.h>
#include<ws2tcpip.h>
#include"User.h"
//#include"GameDatabases.h"
#include"IniDatabases.h"
#include"CheckInput.h"
#include<map>
#include<memory>
#include<iostream>
#include<sstream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;


#define MAX_BUFFER_SIZE 4096
#define IPSERVER "127.0.0.1"
#define PORT 6868

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

class Server
{
private:
	// 
	string IPAddress;
	int Port;
	
	// Save data for Server
	map<string, shared_ptr<User>> ListUser;
	map<int, shared_ptr<GameProperties>> ListGame;

public:
	Server();
	Server(string, int);
	~Server();

	// active Server
	void run();
	// Send a message from Server to Client
	int sendMsg(SOCKET, string);

	//SOCKET waitConnection(SOCKET);


	// Covert Message fro Client to string
	vector<string> getDataMsg(string);
	// Server funcion
	void acceptedAccount(fd_set, SOCKET, SOCKET, vector<string>);
	void logIn(fd_set, SOCKET, SOCKET, vector<string>);
	void registerAccount(fd_set, SOCKET, SOCKET, vector<string>);

	void findGame(fd_set, SOCKET, SOCKET, vector<string>);
	void newGame(fd_set, SOCKET, SOCKET, vector<string>);
	void InGame(fd_set, SOCKET, SOCKET, vector<string>);
	void findInfo(fd_set, SOCKET, SOCKET, vector<string>);
	void findListGamePlayed(fd_set, SOCKET, SOCKET, vector<string>);
	void replayGame(fd_set, SOCKET, SOCKET, vector<string>);
	//
	// Check win game
	bool checkIsFullBoard(shared_ptr<GameProperties>);
	char checkWin(int, int, char, shared_ptr<GameProperties>);
};