#include"IniDatabases.h"

vector<string> Database::getDataFromString(string strData)
{
    vector<string> data;
    string temp;
    temp.clear();
    for (int i = 0; i < strData.size(); i++)
    {
        if (strData[i] == '|')
        {
            data.push_back(temp);
            temp.clear();
            continue;
        }
        temp += strData[i];
    }
    data.push_back(temp);
    temp.clear();

    return data;
}
string Database::convertPlayertoData(shared_ptr<Player> Player)
{
    string NamePlayer = Player->getName();
    int Wins = Player->getWin();
    int Draws = Player->getDraw();
    int Loses = Player->getLose();
    int Rank = Player->getRank();
    ostringstream data;
    data.clear();
    data << NamePlayer << "|" << Wins << "|" << Draws << "|" << Loses << "|" << Rank;
    string strData = data.str();
    return strData;
}
shared_ptr<Player> Database::convertDatatoPlayer(string PlayerData)
{
    vector<string> ListDataPlayer = getDataFromString(PlayerData);

    string NamePlayer = ListDataPlayer[0];
    int Wins = stoi(ListDataPlayer[1]);
    int Draws = stoi(ListDataPlayer[2]);
    int Loses = stoi(ListDataPlayer[3]);
    int Rank = stoi(ListDataPlayer[4]);

    shared_ptr<Player> tPlayer(new Player(NamePlayer, Wins, Draws, Loses));

    return tPlayer;
}
map<string, shared_ptr<Player>> Database::getListPlayer()
{
    string fileName = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/AllPlayerInfo";
    fstream file(fileName + ".ini");

    map<string, shared_ptr<Player>> ListPlayer;

    if (file.fail())
    {
        return ListPlayer;
    }
    else
    {
        ifstream infile;
        infile.open(fileName + ".ini");

        vector<string> ListPlayerData;
        string tempData;
        tempData.clear();
        while (!infile.eof())	//khi chưa tới cuối file thì tiếp tục đọc
        {
            getline(infile, tempData);
            ListPlayerData.push_back(tempData);
            tempData.clear();
        }
        ListPlayerData.pop_back();
        for (int i = 0; i < ListPlayerData.size(); i++)
        {
            shared_ptr<Player> tPlayer = convertDatatoPlayer(ListPlayerData[i]);
            ListPlayer.insert({ tPlayer->getName(), tPlayer });
        }
        return ListPlayer;
    }
    file.close();
}
void Database::addPlayer(shared_ptr<Player> PlayerAdd)
{
    string fileName = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/AllPlayerInfo";
    fstream file(fileName + ".ini");

    if (file.fail())
    {
        ofstream newFile(fileName + ".ini");
        string Data = convertPlayertoData(PlayerAdd);
        newFile << Data << endl;
        Data.clear();
        newFile.close();
    }
    else
    {
        map<string, shared_ptr<Player>> ListPlayer = getListPlayer();

        if (ListPlayer.count(PlayerAdd->getName()) == 1)
        {
            ListPlayer.find(PlayerAdd->getName())->second = PlayerAdd; // Update Player
        }
        else
        {
            ListPlayer.insert({ PlayerAdd->getName(), PlayerAdd }); // Add Player
        }

        ostringstream DataPlayer;
        DataPlayer.clear();
        for (auto i = ListPlayer.begin(); i != ListPlayer.end(); i++)
        {
            DataPlayer << convertPlayertoData(i->second) << endl;
        }
        ofstream newFile(fileName + ".ini", ios::trunc);
        newFile << DataPlayer.str(); 
        DataPlayer.clear();
        newFile.close();
    }
    file.close();
}

bool Database::checkExistName(string NameCheck)
{
    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
    if (ListPlayer.count(NameCheck) == 1)
    {
        return true;
    }
    return false;
}
shared_ptr<Player> Database::findPlayer(string NameFind)
{
    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
    return ListPlayer.find(NameFind)->second;
}
shared_ptr<Player> Database::getSuitablePlayer(string PlayerName, vector<string> ListPlayerFree)
{
    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
    int PlayerRank = ListPlayer.find(PlayerName)->second->getRank();
    vector<int> ListRank;
    for (int i = 0; i < ListPlayerFree.size(); i++)
    {
        ListRank.push_back(ListPlayer.find(ListPlayerFree[i])->second->getRank());
    }
    ListRank.push_back(PlayerRank);
    sort(ListRank.begin(), ListRank.end());

    for (int i = 0; i < ListRank.size(); i++)
    {
        if (ListRank[i] == PlayerRank)
        {
            // If at the end list rank -> get Pre 
            if (i == ListRank.size() - 1)
            {
                for (auto j = ListPlayer.begin(); j != ListPlayer.end(); j++)
                {
                    if (j->second->getRank() == ListRank[i - 1])
                    {
                        if (j->first != PlayerName)
                        {
                            return j->second;
                        }
                    }
                }
            }
            else
            {
                for (auto j = ListPlayer.begin(); j != ListPlayer.end(); j++)
                {
                    if (j->second->getRank() == ListRank[i + 1])
                    {
                        if (j->first != PlayerName)
                        {
                            return j->second;
                        }
                    }
                }
            }
        }
    }
}

void Database::writeIDFile(int IDGame)
{
    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
    fstream file(folder + "ID_Game" + ".ini");

    if (file.fail())
    {
        ofstream newFile(folder + "ID_Game" + ".ini");
        newFile << IDGame;
        newFile.close();
    }
    else
    {
        file << IDGame;
    }
    file.close();
}
int Database::getPreIDGame()
{
    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
    fstream file(folder + "ID_Game" + ".ini");

    if (file.fail())
    {
        ofstream newFile(folder + "ID_Game" + ".ini");
        newFile << 0;
        newFile.close();
        return 0;
    }
    else
    {
        string ID;
        file >> ID;

        return stoi(ID);
    }
    file.close();
}

void Database::recordToPlayerFile(shared_ptr<GameProperties> PlayedGame)
{
    int ID = PlayedGame->getIDGame();
    int sizeBoard = PlayedGame->getSizeBoard();
    string Player1 = PlayedGame->getPlayer1();
    string Player2 = PlayedGame->getPlayer2();
    string Winer = PlayedGame->getWiner();
    vector<shared_ptr<PointChecked>> PointRecord = PlayedGame->getPointRecord();

    ostringstream dataPointRecord;
    dataPointRecord << "{";
    for (int i = 0; i < PointRecord.size(); i++)
    {
        dataPointRecord << "(" << PointRecord[i]->getRow() << PointRecord[i]->getCol() << PointRecord[i]->getChecked() << ")";
    }
    dataPointRecord << "}";

    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
    // Player 1
    fstream file1(folder + Player1 + ".ini");
    if (file1.fail())
    {
        //Create new file
        ofstream newFile(folder + Player1 + ".ini");
        ostringstream PlayerInfo;
        PlayerInfo.clear();
        PlayerInfo << Player1 << endl;
        PlayerInfo << ID;
        PlayerInfo << "|" << Player1;
        PlayerInfo << "|" << Player2;
        PlayerInfo << "|" << Winer;
        PlayerInfo << "|" << sizeBoard;
        PlayerInfo << "|" << dataPointRecord.str();

        newFile << PlayerInfo.str();
        PlayerInfo.clear();
        newFile.close();
    }
    else
    {
        ostringstream PlayerInfo;
        PlayerInfo.clear();
        string temp;
        while (!file1.eof())	//khi chưa tới cuối file thì tiếp tục đọc
        {
            temp.clear();
            getline(file1, temp);
            PlayerInfo << temp << endl;
        }
        /*PlayerInfo << endl;*/
        PlayerInfo << ID;
        PlayerInfo << "|" << Player1;
        PlayerInfo << "|" << Player2;
        PlayerInfo << "|" << Winer;
        PlayerInfo << "|" << sizeBoard;
        PlayerInfo << "|" << dataPointRecord.str();

        ofstream o;
        o.open(folder + Player1 + ".ini");
        o << PlayerInfo.str();
        PlayerInfo.clear();
        o.close();
    }
    file1.close();
    // Player 2
    fstream file2(folder + Player2 + ".ini");
    if (file2.fail())
    {
        //Create new file
        ofstream newFile(folder + Player2 + ".ini");
        ostringstream PlayerInfo;
        PlayerInfo.clear();
        PlayerInfo << Player2 << endl;
        PlayerInfo << ID;
        PlayerInfo << "|" << Player1;
        PlayerInfo << "|" << Player2;
        PlayerInfo << "|" << Winer;
        PlayerInfo << "|" << sizeBoard;
        PlayerInfo << "|" << dataPointRecord.str();

        newFile << PlayerInfo.str();
        PlayerInfo.clear();
        newFile.close();
    }
    else
    {
        ostringstream PlayerInfo;
        PlayerInfo.clear();
        string temp;
        while (!file2.eof())	//khi chưa tới cuối file thì tiếp tục đọc
        {
            temp.clear();
            getline(file2, temp);
            PlayerInfo << temp << endl;
        }
        /*PlayerInfo << endl;*/
        PlayerInfo << ID;
        PlayerInfo << "|" << Player1;
        PlayerInfo << "|" << Player2;
        PlayerInfo << "|" << Winer;
        PlayerInfo << "|" << sizeBoard;
        PlayerInfo << "|" << dataPointRecord.str();

        ofstream o;
        o.open(folder + Player2 + ".ini");
        o << PlayerInfo.str();
        PlayerInfo.clear();
        o.close();
    }
    file2.close();
    dataPointRecord.clear();
}
map<int, shared_ptr<GameRecord>> Database::getListGamePlayed(string PlayerName)
{
    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
    fstream file(folder + PlayerName + ".ini");
    map<int, shared_ptr<GameRecord>> ListGamePlayed;
    if (file.fail())
    {
        return ListGamePlayed;
    }
    else
    {
        ifstream infile;
        infile.open(folder + PlayerName + ".ini");

        vector<string> ListData;
        string tempData;
        tempData.clear();
        while (!infile.eof())	//khi chưa tới cuối file thì tiếp tục đọc
        {
            getline(infile, tempData);
            ListData.push_back(tempData);
            tempData.clear();
        }
        ListData.pop_back();
        for (int i = 1; i < ListData.size(); i++)
        {
            vector<string> dataGame = getDataFromString(ListData[i]);
            int ID = stoi(dataGame[0]);
            string Player1 = dataGame[1];
            string Player2 = dataGame[2];
            string Winer = dataGame[3];
            int sizeBoard = stoi(dataGame[4]);
            string PointRecord = dataGame[5];
            // string -> vector Point string
            vector<string> ListPointString;
            string tempPointString;
            tempPointString.clear();
            for (int i = 0; i < PointRecord.size(); i++)
            {
                if (i == 0 || i == PointRecord.size() - 1 || PointRecord[i] == '(')
                {
                    continue;
                }
                if (PointRecord[i] == ')')
                {
                    ListPointString.push_back(tempPointString);
                    tempPointString.clear();
                    continue;
                }
                tempPointString += PointRecord[i];
            }
            // vector Point string -> vector Point Checked
            vector<shared_ptr<PointChecked>> ListPoint;
            for (int i = 0; i < ListPointString.size(); i++)
            {
                string tPointStr = ListPointString[i];
                int tRow = tPointStr[0];
                int tCol = tPointStr[1];
                char tChecked = tPointStr[2];
                shared_ptr<PointChecked> tPoint(new PointChecked(tRow, tCol, tChecked));
                ListPoint.push_back(tPoint);
                tPointStr.clear();
            }
            //
            shared_ptr<GameRecord> tGame(new GameRecord(ID, sizeBoard, Player1, Player2, Winer, ListPoint));
            ListGamePlayed.insert({ ID, tGame });
        }
        return ListGamePlayed;
    }
    file.close();
}