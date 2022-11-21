#include"Client.h"

Client::Client()
{
	//
}
Client::~Client()
{
	//
}

bool Client::setupDLL()
{
	cout << "Step 1: Set up DLL" << endl;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionResquested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionResquested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The Winsock dll not found!" << endl;
		return false;
	}
	else
	{
		cout << "The Winsock dll found." << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
		return true;
	}
}
SOCKET Client::createSocket()
{
	cout << "Step2: Set up a Client Socket " << endl;
	SOCKET clientSocket;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP Socket
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket()!" << WSAGetLastError() << endl;
		WSACleanup();
		return INVALID_SOCKET;
	}
	else
	{
		cout << "Socket is OK." << endl;
		return clientSocket;
	}
}
void Client::connectToServer()
{
	if (setupDLL() == false)
	{
		cout << "Error at Step 1." << endl;
	}
	else
	{
		SOCKET sockClient = createSocket();
		if (sockClient == INVALID_SOCKET)
		{
			cout << "Error at Step 2." << endl;
		}
		else
		{
			cout << "Step 3: Connect to the Server" << endl;
			sockaddr_in clientService; // used by IP4
			clientService.sin_family = AF_INET;
			InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
			clientService.sin_port = htons(11111);
			if (connect(sockClient, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
			{
				cout << "Client connect(): fail to connect!" << WSAGetLastError() << endl;
				closesocket(sockClient);
				WSACleanup();
			}
			else
			{
				cout << "Client: connect() is OK." << endl;
				cout << "Client: Can start sending and receiving data...." << endl;
				char buffer[MAX_BUFFER_SIZE];
				ZeroMemory(buffer, MAX_BUFFER_SIZE);
				int byteIn = recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
				if (byteIn > 0)
				{
					cout << "==Server: " << buffer << "==" << endl;
					ZeroMemory(buffer, 4096);
					// 
					int chose = IO::inputLoginOrRegister();
					switch (chose)
					{
					case LOG_IN:
					{
						loginToServer(sockClient);
						
						break;
					}
					case REGISTER:
					{
						registerToServer(sockClient);
						
						break;
					}
					}
				}
				else
				{
					WSACleanup();
				}
			}
		}
	}
}


vector<string> Client::getDataMsg(string DataMsg)
{
	vector<string> data;
	string temp;
	temp.clear();
	for (int i = 0; i < DataMsg.size(); i++)
	{
		if (DataMsg[i] == '|')
		{
			data.push_back(temp);
			temp.clear();
			continue;
		}
		temp += DataMsg[i];
	}
	data.push_back(temp);
	temp.clear();
	return data;
}
int Client::sendMsg(SOCKET clientSocket, string mess)
{
	return send(clientSocket, mess.c_str(), mess.size() + 1, 0);
}

void Client::loginToServer(SOCKET sockClient)
{
	system("cls");
	SetConsoleTitle(L"Log In");
	string UserName = IO::inputName();
	ostringstream ss;
	ss << LOG_IN << "|" << UserName;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);
	int ResponeData = stoi(ListData[2]);
	ZeroMemory(buffer, MAX_BUFFER_SIZE);

	if (ResponeData == ACCPETED)
	{
		cout << "Accepted Login." << endl;
		Sleep(1000);
		menu(sockClient, UserName);
	}
	else if (ResponeData == ACCOUT_NOT_EXISTED)
	{
		bool run = true;
		while (run)
		{
			cout << "Account does not exist" << endl;
			string UserName = IO::inputName();
			ostringstream ss;
			ss << LOG_IN << "|" << UserName;
			string strOut = ss.str();
			sendMsg(sockClient, strOut);

			ZeroMemory(buffer, MAX_BUFFER_SIZE);
			recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
			string DataRecv = string(buffer);
			vector<string> ListData = getDataMsg(DataRecv);
			int tResponeData = stoi(ListData[2]);
			ZeroMemory(buffer, MAX_BUFFER_SIZE);
			if (tResponeData == ACCPETED)
			{
				cout << "Accepted Login." << endl;
				run = false;
			}
		}
		Sleep(1000);
		menu(sockClient, UserName);
	}
}
void Client::registerToServer(SOCKET sockClient)
{
	system("cls");
	SetConsoleTitle(L"Register");
	string UserName = IO::inputName();
	ostringstream ss;
	ss.clear();
	ss << REGISTER << "|" << UserName;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);
	int ResponeData = stoi(ListData[2]);
	ZeroMemory(buffer, MAX_BUFFER_SIZE);

	if (ResponeData == ACCPETED)
	{
		cout << "Accepted Register." << endl;
		Sleep(1000);
		menu(sockClient, UserName);
	}
	else if (ResponeData == ACCOUT_EXISTED)
	{
		bool run = true;
		while (run)
		{
			cout << "Account has been exist" << endl;
			string UserName = IO::inputName();
			ostringstream ss;
			ss << REGISTER << "|" << UserName;
			string strOut = ss.str();
			sendMsg(sockClient, strOut);

			ZeroMemory(buffer, MAX_BUFFER_SIZE);
			recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
			string DataRecv = string(buffer);
			vector<string> ListData = getDataMsg(DataRecv);
			int tResponeData = stoi(ListData[2]);
			ZeroMemory(buffer, MAX_BUFFER_SIZE);
			if (tResponeData == ACCPETED)
			{
				cout << "Accepted Register." << endl;
				run = false;
			}
		}
		Sleep(1000);
		menu(sockClient, UserName);
	}
}

void Client::menu(SOCKET sockClient, string ClientName)
{
	system("cls");
	SetConsoleTitle(L"Menu Game");
	bool runMenu = true;
	while (runMenu)
	{
		int funcCode = IO::inputMenu();
		switch (funcCode)
		{
		case PLAYER_INFO:
		{
			findInfo(sockClient, ClientName);
			break;
		}
		case PLAY_GAME:
		{
			playGame(sockClient, ClientName);
			system("pause");
			break;
		}
		case LIST_GAME_PLAYED:
		{
			findListGame(sockClient, ClientName);
			break;
		}
		case GAME_PLAYED:
		{
			replayGame(sockClient, ClientName);
			break;
		}
		case EXIT_FUNCTION:
		{
			runMenu = false;
			break;
		}
		}
	}
	
}

void Client::findInfo(SOCKET sockClient, string ClientName)
{
	system("cls");
	SetConsoleTitle(L"Player Infomation");

	ostringstream ss;
	ss.clear();
	ss << ACCPETED << "|" << ClientName << "|" << FIND_INFO;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);
	
	IO::displayPlayerInfo(ListData[3], stoi(ListData[4]), stoi(ListData[5]), stoi(ListData[6]), stoi(ListData[7]));
	system("pause");
}
void Client::playGame(SOCKET sockClient, string ClientName)
{
	system("cls");
	SetConsoleTitle(L"Game Caro");

	ostringstream ss;
	ss.clear();
	ss << ACCPETED << "|" << ClientName << "|" << FIND_GAME;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	int checkCode = stoi(ListData[2]);
	if (checkCode == NONE_PLAYER)
	{
		cout << "== Server: " << "Chua tim duoc doi thu. Vui long cho he thong sap xep!" << endl;
		ostringstream ss;
		ss.clear();
		ss << ACCPETED << "|" << ClientName << "|" << FIND_GAME << "|" << RESEND;
		string strOut = ss.str();
		sendMsg(sockClient, strOut);

		char buffer1[MAX_BUFFER_SIZE];
		ZeroMemory(buffer1, MAX_BUFFER_SIZE);
		recv(sockClient, buffer1, MAX_BUFFER_SIZE, 0);
		// waitting
		string DataRecv1 = string(buffer1);
		vector<string> ListData1 = getDataMsg(DataRecv1);
		ZeroMemory(buffer1, MAX_BUFFER_SIZE);
		int checkCode1 = stoi(ListData1[2]);
		if (checkCode1 == NEW_GAME)
		{
			cout << "Da tim thay doi thu!" << endl;
			if (ListData1[3] == "H")
			{
				cout << "Quyen cua ban la chu!" << endl;
			}
			cout << "ID game: " << stoi(ListData1[4]) << endl;
			cout << "Opponent infomation" << endl;
			IO::displayPlayerInfo(ListData1[5], stoi(ListData1[6]), stoi(ListData1[7]), stoi(ListData1[8]), stoi(ListData1[9]));
			int IDgame = stoi(ListData1[4]);
			int SizeBoard = IO::inputSizeBoard();
			ostringstream ss1;
			ss1.clear();
			ss1 << ACCPETED << "|" << ClientName << "|" << NEW_GAME << "|" << IDgame << "|" << "H" << "|" << SizeBoard << "|" << ListData1[5];
			string strOut1 = ss1.str();
			sendMsg(sockClient, strOut1);

			system("pause");
			inGame(sockClient, ClientName);
		}
	}
	else if (checkCode == NEW_GAME)
	{
		cout << "Da tim thay doi thu!" << endl;
		if (ListData[3] == "G")
		{
			cout << "Quyen cua ban la khach!" << endl;
		}
		cout << "ID game: " << ListData[4] << endl;
		cout << "Opponent infomation" << endl;
		IO::displayPlayerInfo(ListData[5], stoi(ListData[6]), stoi(ListData[7]), stoi(ListData[8]), stoi(ListData[9]));
		cout << "Hay cho chu van dau nhap kich thuoc cua ban co." << endl;

		int IDGame = stoi(ListData[4]);
		ostringstream ss1;
		ss1.clear();
		ss1 << ACCPETED << "|" << ClientName << "|" << NEW_GAME << "|" << IDGame << "|" << "G" << "|" << "Yes";
		string strOut1 = ss1.str();
		sendMsg(sockClient, strOut1);
		system("pause");
		inGame(sockClient, ClientName);
	}
}

void Client::inGame(SOCKET sockClient, string ClientName)
{
	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	system("cls");
	if (stoi(ListData[2]) == IN_GAME && ListData[3] == "H")
	{
		int IDGame = stoi(ListData[4]);
		int sizeBoard = stoi(ListData[5]);
		string Player1 = ListData[1];
		string Player2 = ListData[6];
		IO::displayBoard(sizeBoard, Player1, Player2);
		char Turn1 = 'X';
		bool isEnd = true;
		while (isEnd)
		{
			
			if (Turn1 == 'X')
			{
				SettingWindow::gotoXY(0, 2 * sizeBoard + 4);
				SettingWindow::textColor(0, 14);
				cout << "Turn: Play 1 <X>";

				// Replace console window
				for (int i = 0; i < 100; i++)
				{
					for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
					{
						SettingWindow::gotoXY(i, j);
						cout << " ";
					}
				}
				cout << endl;

				SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
				cout << "Enter position of checked point: " << endl;
				cout << "Row: " << endl;
				int rRow = IO::inputValidIndex(sizeBoard);
				cout << "Col: " << endl;
				int rCol = IO::inputValidIndex(sizeBoard);

				ostringstream ss;
				ss.clear();
				ss << ACCPETED << "|" << ClientName << "|" << IN_GAME << "|" << IDGame << "|" << "H" << "|" << rRow << "|" << rCol << "|" << Turn1;
				string strOut = ss.str();
				sendMsg(sockClient, strOut);

				changeTurn(Turn1);
			}
			if (Turn1 == 'O')
			{
				char buffer1[MAX_BUFFER_SIZE];
				ZeroMemory(buffer1, MAX_BUFFER_SIZE);
				recv(sockClient, buffer1, MAX_BUFFER_SIZE, 0);
				string DataRecv1 = string(buffer1);
				vector<string> ListData1 = getDataMsg(DataRecv1);
				ZeroMemory(buffer1, MAX_BUFFER_SIZE);
				if (ListData1.size() == 6)
				{
					if (ListData1[5] == "Invalid")
					{
						SettingWindow::textColor(0, 4);
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "Invalid point." << endl;
						changeTurn(Turn1);
						continue;
					}
					if (ListData1[5] == "Disconnect")
					{
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Your opponent has lost connection. Game canceled" << endl;
						isEnd = false;
						break;
					}
				}
				if (ListData1.size() == 9)
				{
					if (stoi(ListData1[4]) == WIN)
					{
						int Row = stoi(ListData1[6]);
						int Col = stoi(ListData1[7]);
						const char* tempChecked = ListData1[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						string Winer = ListData1[1];
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: You Win." << endl;
						SettingWindow::gotoXY(0, 2 * sizeBoard + 6);
						cout << "Winer: " << Winer << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData1[4]) == LOSE)
					{
						int Row = stoi(ListData1[6]);
						int Col = stoi(ListData1[7]);
						const char* tempChecked = ListData1[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						string Winer = ListData1[5];
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: You Lose." << endl;
						SettingWindow::gotoXY(0, 2 * sizeBoard + 6);
						cout << "Winer: " << Winer << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData1[4]) == DRAW1)
					{
						int Row = stoi(ListData1[6]);
						int Col = stoi(ListData1[7]);
						const char* tempChecked = ListData1[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: Draw" << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData1[4]) == DRAW2)
					{
						int Row = stoi(ListData1[6]);
						int Col = stoi(ListData1[7]);
						const char* tempChecked = ListData1[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: Draw" << endl;
						isEnd = false;
						break;
					}
				}
				if (ListData1.size() == 8)
				{	
					if (stoi(ListData1[4]) == YOUR_POINT)
					{
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "                " << endl;

						int Row = stoi(ListData1[5]);
						int Col = stoi(ListData1[6]);
						const char* tempChecked = ListData1[7].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						continue;
					}
					if (stoi(ListData1[4]) == OPPONENT_POINT)
					{
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "                " << endl;

						SettingWindow::gotoXY(0, 2 * sizeBoard + 4);
						SettingWindow::textColor(0, 14);
						cout << "Turn: Play 2 <O>";

						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;
						/*Sleep(1000);*/
						int Row = stoi(ListData1[5]);
						int Col = stoi(ListData1[6]);
						const char* tempChecked = ListData1[7].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						changeTurn(Turn1);
						continue;
					}
				}
			}
		}
	}
	if (stoi(ListData[2]) == IN_GAME && ListData[3] == "G")
	{
		int IDGame = stoi(ListData[4]);
		int sizeBoard = stoi(ListData[5]);
		string Player1 = ListData[6];
		string Player2 = ListData[1];
		IO::displayBoard(sizeBoard, Player1, Player2);
		char Turn2 = 'X';
		bool isEnd = true;
		while (isEnd)
		{
			if (Turn2 == 'O')
			{
				SettingWindow::gotoXY(0, 2 * sizeBoard + 4);
				SettingWindow::textColor(0, 14);
				cout << "Turn: Play 2 <O>";

				// Replace console window
				for (int i = 0; i < 100; i++)
				{
					for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
					{
						SettingWindow::gotoXY(i, j);
						cout << " ";
					}
				}
				cout << endl;

				SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
				cout << "Enter position of checked point: " << endl;
				cout << "Row: " << endl;
				int rRow = IO::inputValidIndex(sizeBoard);
				cout << "Col: " << endl;
				int rCol = IO::inputValidIndex(sizeBoard);

				ostringstream ss;
				ss.clear();
				ss << ACCPETED << "|" << ClientName << "|" << IN_GAME << "|" << IDGame << "|" << "H" << "|" << rRow << "|" << rCol << "|" << Turn2;
				string strOut = ss.str();
				sendMsg(sockClient, strOut);
				
				changeTurn(Turn2);
			}
			if (Turn2 == 'X')
			{
				char buffer2[MAX_BUFFER_SIZE];
				ZeroMemory(buffer2, MAX_BUFFER_SIZE);
				recv(sockClient, buffer2, MAX_BUFFER_SIZE, 0);
				string DataRecv2 = string(buffer2);
				vector<string> ListData2 = getDataMsg(DataRecv2);
				ZeroMemory(buffer2, MAX_BUFFER_SIZE);
				if (ListData2.size() == 6)
				{
					if (ListData2[5] == "Invalid")
					{
						SettingWindow::textColor(0, 4);
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "Invalid point." << endl;
						changeTurn(Turn2);
						continue;
					}
					if (ListData2[5] == "Disconnect")
					{
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Your opponent has lost connection. Game canceled" << endl;
						isEnd = false;
						break;
					}
				}
				if (ListData2.size() == 9)
				{
					if (stoi(ListData2[4]) == WIN)
					{
						int Row = stoi(ListData2[6]); 
						int Col = stoi(ListData2[7]);
						const char* tempChecked = ListData2[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						string Winer = ListData2[1];
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: You Win." << endl;
						SettingWindow::gotoXY(0, 2 * sizeBoard + 6);
						cout << "Winer: " << Winer << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData2[4]) == LOSE)
					{
						int Row = stoi(ListData2[6]);
						int Col = stoi(ListData2[7]);
						const char* tempChecked = ListData2[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						string Winer = ListData2[5];
						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: You Lose." << endl;
						SettingWindow::gotoXY(0, 2 * sizeBoard + 6);
						cout << "Winer: " << Winer << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData2[4]) == DRAW1)
					{
						int Row = stoi(ListData2[6]);
						int Col = stoi(ListData2[7]);
						const char* tempChecked = ListData2[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: Draw" << endl;
						isEnd = false;
						break;
					}
					if (stoi(ListData2[4]) == DRAW2)
					{
						int Row = stoi(ListData2[6]);
						int Col = stoi(ListData2[7]);
						const char* tempChecked = ListData2[8].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);
						// Replace console window
						for (int i = 0; i < 100; i++)
						{
							for (int j = 2 * sizeBoard + 5; j < 2 * sizeBoard + 10; j++)
							{
								SettingWindow::gotoXY(i, j);
								cout << " ";
							}
						}
						cout << endl;

						SettingWindow::textColor(0, 14);
						SettingWindow::gotoXY(0, 2 * sizeBoard + 5);
						cout << "Game Over: Draw" << endl;
						isEnd = false;
						break;
					}
				}
				if (ListData2.size() == 8)
				{
					if (stoi(ListData2[4]) == YOUR_POINT)
					{
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "                " << endl;

						int Row = stoi(ListData2[5]);
						int Col = stoi(ListData2[6]);
						const char* tempChecked = ListData2[7].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						continue;
					}
					if (stoi(ListData2[4]) == OPPONENT_POINT)
					{
						SettingWindow::gotoXY(4 * sizeBoard + 5, 5);
						cout << "                " << endl;

						SettingWindow::gotoXY(0, 2 * sizeBoard + 4);
						SettingWindow::textColor(0, 14);
						cout << "Turn: Play 1 <X>";
						/*Sleep(1000);*/
						int Row = stoi(ListData2[5]);
						int Col = stoi(ListData2[6]);
						const char* tempChecked = ListData2[7].c_str();
						char Checked = *tempChecked;
						IO::displayPointChecked(Row, Col, Checked);

						changeTurn(Turn2);
						continue;
					}
				}
			}
		}
	}
}
void Client::findListGame(SOCKET sockClient, string ClientName)
{
	system("cls");
	SetConsoleTitle(L"List Game Played");

	ostringstream ss;
	ss.clear();
	ss << ACCPETED << "|" << ClientName << "|" << LIST_REPLAY;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);

	if (ListData.size() == 4)
	{
		if (ListData[3] == "No Data")
		{
			cout << "Khong co du lieu van game da choi. Ban chua choi van nao. Hay chon New Game!" << endl;
		}
	}
	else
	{
		for (int i = 3; i < ListData.size(); i++)
		{
			cout << "ID = " << ListData[i] << endl;
		}
	}
	system("pause");
}
void Client::replayGame(SOCKET sockClient, string ClientName)
{
	SetConsoleTitle(L"Replay Game");

	int IDgame = IO::inputIDGamePlayed();
	ostringstream ss;
	ss.clear();
	ss << ACCPETED << "|" << ClientName << "|" << REPLAY_GAME << "|" << IDgame;
	string strOut = ss.str();
	sendMsg(sockClient, strOut);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	recv(sockClient, buffer, MAX_BUFFER_SIZE, 0);
	string DataRecv = string(buffer);
	vector<string> ListData = getDataMsg(DataRecv);

	if (ListData.size() == 4)
	{
		if (ListData[3] == "No game")
		{
			cout << "Game ID = " << IDgame << " is not existed." << endl;
		}
		system("pause");
	}
	else
	{
		IO::displayGamePlayed(ListData);
	}
}
void Client::changeTurn(char& Turn)
{
	if (Turn == 'X')
	{
		Turn = 'O';
	}
	else if (Turn == 'O')
	{
		Turn = 'X';
	}
}