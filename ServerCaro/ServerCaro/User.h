#pragma once
#include<string>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class User
{
private:
	SOCKET Sock;
	string UserName;
	string StatusConnect = "Free";
public:
	User();
	User(SOCKET, string);
	~User();

	void setSock(SOCKET);
	void setUserName(string);
	void setStatusConnect(string);

	SOCKET getSock();
	string getUserName();
	string getStatusConnect();
};