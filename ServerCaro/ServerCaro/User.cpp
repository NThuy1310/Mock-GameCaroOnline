#include"User.h"

User::User()
{
	//
}
User::User(SOCKET Sock, string UserName)
{
	this->Sock = Sock;
	this->UserName = UserName;
	this->StatusConnect = "Free";
}
User::~User()
{
	//
}

void User::setSock(SOCKET Sock)
{
	this->Sock = Sock;
}
void User::setUserName(string UserName)
{
	this->UserName = UserName;
}
void User::setStatusConnect(string StatusConnect)
{
	this->StatusConnect = StatusConnect;
}

SOCKET User::getSock()
{
	return Sock;
}
string User::getUserName()
{
	return UserName;
}
string User::getStatusConnect()
{
	return StatusConnect;
}