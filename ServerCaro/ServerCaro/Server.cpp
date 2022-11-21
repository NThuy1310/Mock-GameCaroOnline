#include"Server.h"

Server::Server()
{
	//
}
Server::Server(string IPAddress, int Port)
{
    this->IPAddress = IPAddress;
    this->Port = Port;
}
Server::~Server()
{
   WSACleanup();
}

void Server::run()
{
	// 1: Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0)
	{
		cout << "Can't initialize winsock! Quitting." << endl;
		return;
	}

	// 2: Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cout << "Can't create a socket! Quitting." << endl;
		return;
	}

	// 3: Bind the IP address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(11111);
	/*hint.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");*/
	/*hint.sin_addr.S_un.S_addr = INADDR_ANY;*/
	inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// 4: Tell winsock the socket is for listening

	listen(listening, SOMAXCONN);

	// 5: Create the file descriptor set and zero it
	cout << "Server Caro: Running";
	fd_set master;
	FD_ZERO(&master);

	// 
	FD_SET(listening, &master);

	bool run = true;

	while (run)
	{
		fd_set copy = master;
		// See who is talking
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		// Loop through all the current connections/ potential connect
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			// Is it an inbound communication
			if (sock == listening)
			{
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);
				// Add new connection to the list of connection clients
				FD_SET(client, &master);
				// Send a welcome message to the connected client
				string welcomeMsg = "Welcome to the Game Server";
				sendMsg(client, welcomeMsg);
			}
			else
			{
				char buf[MAX_BUFFER_SIZE];
				ZeroMemory(buf, MAX_BUFFER_SIZE);
				// Receive message
				int bytesIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
				if (bytesIn <= 0)
				{
                    string DisconnectUserName;
                    for (auto i = ListUser.begin(); i != ListUser.end(); i++)
                    {
                        if (i->second->getSock() == sock)
                        {
                            DisconnectUserName = i->first;
                            
                            ListUser.erase(i->first);
                            break;
                        }
                    }
                    for (auto i = ListGame.begin(); i != ListGame.end(); i++)
                    {
                        if (i->second->getPlayer1() == DisconnectUserName)
                        {
                            string OpponentName = i->second->getPlayer2();
                            int IdGame = i->first;
                            ostringstream ss;
                            ss.clear();
                            ss << ACCPETED << "|" << OpponentName << "|" << IN_GAME << "|" << IdGame << "|" << OpponentName << "|" << "Disconnect";
                            string strOut = ss.str();
                            sendMsg(ListUser.find(OpponentName)->second->getSock(), strOut);
                            ListGame.erase(i->first);
                            break;
                        }
                        if (i->second->getPlayer2() == DisconnectUserName)
                        {
                            string OpponentName = i->second->getPlayer1();
                            int IdGame = i->first;
                            ostringstream ss;
                            ss.clear();
                            ss << ACCPETED << "|" << OpponentName << "|" << IN_GAME << "|" << IdGame << "|" << OpponentName << "|" << "Disconnect";
                            string strOut = ss.str();
                            sendMsg(ListUser.find(OpponentName)->second->getSock(), strOut);
                            ListGame.erase(i->first);
                            break;
                        }
                    }
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					string dataMsg = string(buf);
					vector<string> ListData = getDataMsg(dataMsg);
					int codeStatus = stoi(ListData[0]);
					switch (codeStatus)
					{
					case LOG_IN:
					{
                        logIn(master, listening, sock, ListData);
                        break;
					}
                    case REGISTER:
                    {
                        registerAccount(master, listening, sock, ListData);
                        break;
                    }
                    case ACCPETED:
                    {
						acceptedAccount(master, listening, sock, ListData);
						break;
                    }
					}
				}
			}
		}
	}
}
int Server::sendMsg(SOCKET clientSocket, string mess)
{
    return send(clientSocket, mess.c_str(), mess.size() + 1, 0);
}
vector<string> Server::getDataMsg(string DataMsg)
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

// Server funcion
void Server::acceptedAccount(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
	int funcCode = stoi(ListData[2]);
	switch (funcCode)
	{
	case FIND_INFO:
	{
		findInfo(master, listening, sock, ListData);
		break;
	}
	case FIND_GAME:
	{
        findGame(master, listening, sock, ListData);
		break;
	}
	case NEW_GAME:
	{
		newGame(master, listening, sock, ListData);
		break;
	}
	case IN_GAME:
	{
        InGame(master, listening, sock, ListData);
		break;
	}
	case LIST_REPLAY:
	{
        findListGamePlayed(master, listening, sock, ListData);
		break;
	}
	case REPLAY_GAME:
	{
        replayGame(master, listening, sock, ListData);
		break;
	}
	}
}
void Server::logIn(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
    string NameCheck = ListData[1];
    if (Database::checkExistName(NameCheck) && ListUser.count(NameCheck) == 0)
    {
        shared_ptr<User> oldUser(new User(sock, NameCheck));
        ListUser.insert({ NameCheck , oldUser });

        ostringstream ss;
        ss << LOG_IN << "|" << NameCheck << "|" << ACCPETED;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        strOut.clear();
    }
    else
    {
        ostringstream ss;
        ss << LOG_IN << "|" << NameCheck << "|" << ACCOUT_NOT_EXISTED;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        // Client send request log in again
        strOut.clear();
    }
}
void Server::registerAccount(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
    string NameCheck = ListData[1];
    if (Database::checkExistName(NameCheck))
    {
        ostringstream ss;
        ss << REGISTER << "|" << NameCheck << "|" << ACCOUT_EXISTED;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        // Client send request again
        strOut.clear();
    }
    else
    {
        shared_ptr<User> newUser(new User(sock, NameCheck));
        ListUser.insert({ NameCheck , newUser });
		shared_ptr<Player> newPlayer(new Player(NameCheck));
		Database::addPlayer(newPlayer);

        ostringstream ss;
		ss << REGISTER << "|" << NameCheck << "|" << ACCPETED;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        strOut.clear();
    }
}
void Server::findInfo(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
	string userName = ListData[1];

	shared_ptr<Player> tPlayer = Database::findPlayer(userName);
	string tPlayerData = Database::convertPlayertoData(tPlayer);

    ostringstream ss;
	ss.clear();
    ss << ACCPETED << "|" << userName << "|" << FIND_INFO << "|" << tPlayerData;
    string strOut = ss.str();
    sendMsg(sock, strOut);
}
void Server::findGame(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
	if (ListData.size() == 4 && stoi(ListData[3]) == RESEND)
	{
		return;
	}
    string userName = ListData[1];
    shared_ptr<Player> HandlingPlayer = Database::findPlayer(userName);
    shared_ptr<User> HandlingUser = ListUser.find(userName)->second;
	if (HandlingUser->getStatusConnect() != "Busy")
	{
		HandlingUser->setStatusConnect("Busy");
	}
	string HandlingPlayerData = Database::convertPlayertoData(HandlingPlayer);

    vector<string> ListUserName;
    for (auto i = ListUser.begin(); i != ListUser.end(); i++)
    {
        if (i->first != userName)
        {
            if (i->second->getStatusConnect() == "Busy")
            {
                bool flag = false;
                for (auto j = ListGame.begin(); j != ListGame.end(); j++)
                {
                    if (j->second->getPlayer1() == i->first || j->second->getPlayer2() == i->first)
                    {
                        flag = true;
                    }
                }
                if (!flag)
                {
                    ListUserName.push_back(i->first);
                }
            }
        }
    }
    if (ListUserName.size() == 0)
    {
        ostringstream ss;
        ss << ACCPETED << "|" << userName << "|" << NONE_PLAYER;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        // Client need send request again
    }
    else
    {
		shared_ptr<Player> OpponentPlayer = Database::getSuitablePlayer(userName, ListUserName);
		shared_ptr<User> OpponentUser = ListUser.find(OpponentPlayer->getName())->second;
		string OpponentPlayerData = Database::convertPlayertoData(OpponentPlayer);

        int IDGame = Database::getPreIDGame() + 1;
        Database::writeIDFile(IDGame);

        ostringstream ss;
		ss.clear();
        ss << ACCPETED << "|" << OpponentUser->getUserName() << "|" << NEW_GAME << "|" << "H" << "|" << IDGame << "|" << HandlingPlayerData;
        string strOut = ss.str();
        sendMsg(OpponentUser->getSock(), strOut);

        // Send to user who fiding Game
        ostringstream ss1;
		ss1.clear();
        ss1 << ACCPETED << "|" << userName << "|" << NEW_GAME << "|" << "G" << "|" << IDGame << "|" << OpponentPlayerData;
        string strOut1 = ss1.str();
        sendMsg(sock, strOut1);
    }
}
void Server::newGame(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
	if (ListData[4] == "H")
	{
		int IDGame = stoi(ListData[3]);
		int SizeBoard = stoi(ListData[5]);
		string Player1 = ListData[1];
		string Player2 = ListData[6];

		shared_ptr<GameProperties> newCaro(new GameProperties(IDGame, SizeBoard, Player1, Player2));
		newCaro->initializeDefaultBoard(SizeBoard);

		ListGame.insert({ newCaro->getIDGame(), newCaro });

		ostringstream ss;
		ss.clear();
		ss << ACCPETED << "|" << Player1 << "|" << IN_GAME << "|" << "H" << "|" << IDGame << "|" << SizeBoard << "|" << Player2;
		string strOut = ss.str();
		sendMsg(sock, strOut);

		shared_ptr<User> OpponentUser = ListUser.find(Player2)->second;
		ostringstream ss1;
		ss1.clear();
		ss1 << ACCPETED << "|" << Player2 << "|" << IN_GAME << "|" << "G" << "|" << IDGame << "|" << SizeBoard << "|" << Player1;
		string strOut1 = ss1.str();
		sendMsg(OpponentUser->getSock(), strOut1);
	}
	if (ListData[4] == "G")
	{
		if (ListData[5] == "Yes")
		{
			return;
		}
	}
}
void Server::InGame(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
    string userName = ListData[1];
    int idGame = stoi(ListData[3]);
    int row = stoi(ListData[5]);
    int col = stoi(ListData[6]);
    const char* tempChecked = ListData[7].c_str();
    char checked = *tempChecked;

    shared_ptr<Player> HadlingPlayer = Database::findPlayer(userName);
    shared_ptr<User> HadlingUser = ListUser.find(userName)->second;


    shared_ptr<GameProperties> GamePlaying = ListGame.find(idGame)->second;
    if (CheckInput::checkInvalidPoint(row, col, GamePlaying))
    {
        Sleep(500);
        ostringstream ss;
        ss.clear();
        ss << ACCPETED << "|" << userName << "|" << IN_GAME << "|" << idGame << "|" << userName << "|" << "Invalid";
        string strOut = ss.str();
        sendMsg(sock, strOut);
        return;
    }
    shared_ptr<PointChecked> newPointRecord(new PointChecked(row, col, checked));
    GamePlaying->addCheckedPoint(row, col, checked);
    GamePlaying->addRecordPoint(newPointRecord);
   

    string OpponentName;
    if (GamePlaying->getPlayer1() == userName)
    {
        OpponentName = GamePlaying->getPlayer2();
    }
    if (GamePlaying->getPlayer2() == userName)
    {
        OpponentName = GamePlaying->getPlayer1();
    }
    shared_ptr<Player> OpponentPlayer = Database::findPlayer(OpponentName);
    shared_ptr<User> OpponentUser = ListUser.find(OpponentName)->second;

    if (checkWin(row, col, checked, GamePlaying) == checked)
    {
        Sleep(500);
        // HadlingUser win
        HadlingPlayer->setWin(HadlingPlayer->getWin() + 1);
        OpponentPlayer->setLose(OpponentPlayer->getLose() + 1);
        GamePlaying->setWiner(userName);
        // Update List player
        Database::addPlayer(HadlingPlayer);
        Database::addPlayer(OpponentPlayer);
        // Update Player File
        Database::recordToPlayerFile(GamePlaying);
        // Send result to this client
        ostringstream ss;
        ss.clear();
        ss << ACCPETED << "|" << userName << "|" << IN_GAME << "|" << idGame << "|" << WIN << "|" << OpponentName << "|" << row << "|" << col << "|" << checked;
        string strOut = ss.str();
        sendMsg(sock, strOut);
        // Send result to opponent client
        ostringstream ss1;
        ss1.clear();
        ss1 << ACCPETED << "|" << OpponentName << "|" << IN_GAME << "|" << idGame << "|" << LOSE << "|" << userName << "|" << row << "|" << col << "|" << checked;
        string strOut1 = ss1.str();
        sendMsg(OpponentUser->getSock(), strOut1);
        // Change status of 2 client
        HadlingUser->setStatusConnect("Free");
        OpponentUser->setStatusConnect("Free");
        ListGame.erase(idGame);
        return;
    }
    else if (checkWin(row, col, checked, GamePlaying) == 'D')
    {
        Sleep(500);
        // Draw
        HadlingPlayer->setDraw(HadlingPlayer->getDraw() + 1);
        OpponentPlayer->setDraw(OpponentPlayer->getDraw() + 1);
        GamePlaying->setWiner("D");
        // Update List player
        Database::addPlayer(HadlingPlayer);
        Database::addPlayer(OpponentPlayer);
        // Update Player File
        Database::recordToPlayerFile(GamePlaying);

        ostringstream ss;
        ss.clear();
        ss << ACCPETED << "|" << userName << "|" << IN_GAME << "|" << idGame << "|" << DRAW1 << "|" << OpponentName << "|" << row << "|" << col << "|" << checked;
        string strOut = ss.str();
        sendMsg(sock, strOut);

        ostringstream ss1;
        ss1.clear();
        ss1 << ACCPETED << "|" << OpponentName << "|" << IN_GAME << "|" << idGame << "|" << DRAW2 << "|" << userName << "|" << row << "|" << col << "|" << checked;
        string strOut1 = ss1.str();
        sendMsg(OpponentUser->getSock(), strOut1);

        HadlingUser->setStatusConnect("Free");
        OpponentUser->setStatusConnect("Free");
        ListGame.erase(idGame);
        return;
    }
    else
    {
        Sleep(500);
        ostringstream ss;
        ss.clear();
        ss << ACCPETED << "|" << OpponentName << "|" << IN_GAME << "|" << idGame << "|" << OPPONENT_POINT << "|" << row << "|" << col << "|" << checked;
        string strOut = ss.str();
        sendMsg(OpponentUser->getSock(), strOut);

        ostringstream ss1;
        ss1.clear();
        ss1 << ACCPETED << "|" << userName << "|" << IN_GAME << "|" << idGame << "|" << YOUR_POINT << "|" << row << "|" << col << "|" << checked;
        string strOut1 = ss1.str();
        sendMsg(sock, strOut1);
        // Update ListGame
        ListGame.find(idGame)->second = GamePlaying;
    }
}
void Server::findListGamePlayed(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
    string userName = ListData[1];
    map<int, shared_ptr<GameRecord>> ListGamePlayed = Database::getListGamePlayed(userName);

    ostringstream ss;
    ss.clear();
    ss << ACCPETED << "|" << userName << "|" << LIST_REPLAY;
    if (ListGamePlayed.size() == 0)
    {
        ss << "|" << "No Data";
        string strOut = ss.str();
        sendMsg(sock, strOut);
    }
    else
    {
        for (auto i = ListGamePlayed.begin(); i != ListGamePlayed.end(); i++)
        {
            ss << "|" << i->first;
        }
        string strOut = ss.str();
        sendMsg(sock, strOut);
    }
}

void Server::replayGame(fd_set master, SOCKET listening, SOCKET sock, vector<string> ListData)
{
    string userName = ListData[1];
    int IDGame = stoi(ListData[3]);
    map<int, shared_ptr<GameRecord>> ListGamePlayed = Database::getListGamePlayed(userName);
    ostringstream ss;
    ss.clear();
    ss << ACCPETED << "|" << userName << "|" << REPLAY_GAME;
    if (ListGamePlayed.count(IDGame) == 0)
    {
        ss << "|" << "No game";

        string strOut = ss.str();
        sendMsg(sock, strOut);
    }
    else
    {
        shared_ptr<GameRecord> tGamePlayed = ListGamePlayed.find(IDGame)->second;
        int IDGame = tGamePlayed->getID(); // 3
        int SizeBoard = tGamePlayed->getSizeBoard();
        string Player1 = tGamePlayed->getPlayer1();
        string Player2 = tGamePlayed->getPlayer2();
        string Winer = tGamePlayed->getWiner();
        vector<shared_ptr<PointChecked>> tListPoint = tGamePlayed->getPointRecord();

        ss << "|" << IDGame << "|" << SizeBoard << "|" << Player1 << "|" << Player2 << "|" << Winer;
        for (auto i : tListPoint)
        {
            ss << "|" << i->getRow() << "|" << i->getCol() << "|" << i->getChecked();
        }
        string strOut = ss.str();
        sendMsg(sock, strOut);
    }
}

bool Server::checkIsFullBoard(shared_ptr<GameProperties> GamePlaying)
{
    if (GamePlaying->getSizeBoard() * GamePlaying->getSizeBoard() == GamePlaying->getNumOfTurn())
    {
        return true;
    }
    return false;
}
char Server::checkWin(int Row, int Col, char Checked, shared_ptr<GameProperties> GamePlaying)
{
    if (!checkIsFullBoard(GamePlaying))
    {
        // Check Win
        vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
        int SizeBoard = GamePlaying->getSizeBoard();

        int Count = 1;
        int Step = 1;

        // Check by row
            //Check Right
        while (Col + Step < SizeBoard)
        {
            if (BoardCheck[Row][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
        //Check Left
        while (Col - Step >= 0)
        {
            if (BoardCheck[Row][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by column
            //Check Down
        while (Row + Step < SizeBoard)
        {
            if (BoardCheck[Row + Step][Col] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
        //Check Up
        while (Row - Step >= 0)
        {
            if (BoardCheck[Row - Step][Col] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by right diagonal
            //Check Down
        while (((Row + Step) < SizeBoard) && ((Col + Step) < SizeBoard))
        {
            if (BoardCheck[Row + Step][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }

        }
        //Check Up
        while (((Row - Step) >= 0) && ((Col - Step) >= 0))
        {
            if (BoardCheck[Row - Step][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
        // Check by Left diagonal
            //Check Down
        while (((Row + Step) < SizeBoard) && ((Col - Step) >= 0))
        {
            if (BoardCheck[Row + Step][Col - Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                break;
            }
        }
        //Check Up
        while (((Row - Step) >= 0) && ((Col + Step) < SizeBoard))
        {
            if (BoardCheck[Row - Step][Col + Step] == Checked)
            {
                Count++;
                if (Count == 4)
                {
                    return Checked;
                }
                Step++;
            }
            else
            {
                Step = 1;
                Count = 1;
                break;
            }
        }
    }
    else if (checkIsFullBoard(GamePlaying))
    {
        //Case: Draw
        return 'D';
    }
}