//#include"GameDatabases.h"
//
//// return TRUE if player name is existed
//bool GameDatabase::checkExistName(string Name)
//{
//    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
//    if (ListPlayer.count(Name) == 1 || ListPlayer.size() == 0)
//    {
//        return true;
//    }
//    return false;
//}
//// add player to AfPlayerInfo
//void GameDatabase::addPlayer(shared_ptr<Player> addPlayer)
//{
//    string fileName = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/AllPlayerInfo";
//    fstream file(fileName + ".json");
//
//    if (file.fail())
//    {
//        ofstream newFile(fileName + ".json");
//        json j;
//        string NamePlayer = addPlayer->getName();
//        j[NamePlayer] = { {"Name", addPlayer->getName()}, {"Wins", addPlayer->getWin()},  {"Draws", addPlayer->getDraw()}, {"Loses", addPlayer->getLose()}, {"Rank", addPlayer->getRank()} };
//        newFile << setw(4) << j << endl;
//    }
//    else
//    {
//        json data = json::parse(file);
//        // Can add new or update Player Info
//        string Name = addPlayer->getName();
//        data[Name] = { {"Name", addPlayer->getName()}, {"Wins", addPlayer->getWin()},  {"Draws", addPlayer->getDraw()}, {"Loses", addPlayer->getLose()}, {"Rank", addPlayer->getRank()} };
//        ofstream o;
//        o.open(fileName + ".json");
//        o << setw(4) << data << endl;
//    }
//    file.close();
//}
//// Get list player from databases
//map<string, shared_ptr<Player>> GameDatabase::getListPlayer()
//{
//    string fileName = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/AllPlayerInfo";
//    fstream file(fileName + ".json");
//    map<string, shared_ptr<Player>> ListPlayer;
//    if (file.fail())
//    {
//        return ListPlayer;
//    }
//    else
//    {
//        json data = json::parse(file);
//        
//        for (json::iterator i = data.begin(); i != data.end(); i++)
//        {
//            shared_ptr<Player> tPlayer;
//            json tJson = i.value();
//            from_json(tJson, tPlayer);
//            string name = i.key();
//            ListPlayer.insert({ name, tPlayer });
//        }
//        return ListPlayer;
//    }
//    file.close();
//}
//
//
//shared_ptr<Player> GameDatabase::findPlayer(string findName)
//{
//    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
//    return ListPlayer.find(findName)->second;
//}
//shared_ptr<Player> GameDatabase::getSuitablePlayer(string PlayerName, vector<string> ListPlayerOnline)
//{
//    map<string, shared_ptr<Player>> ListPlayer = getListPlayer();
//    int PlayerRank = ListPlayer.find(PlayerName)->second->getRank();
//    vector<int> ListRank;
//    for (int i = 0; i < ListPlayerOnline.size(); i++)
//    {
//        ListRank.push_back(ListPlayer.find(ListPlayerOnline[i])->second->getRank());
//    }
//    ListRank.push_back(PlayerRank);
//    sort(ListRank.begin(), ListRank.end());
//
//    for (int i = 0; i < ListRank.size(); i++)
//    {
//        if (ListRank[i] == PlayerRank)
//        {
//            // If at the end list rank -> get Pre 
//            if (i == ListRank.size() - 1)
//            {
//                for (auto j = ListPlayer.begin(); j != ListPlayer.end(); j++)
//                {
//                    if (j->second->getRank() == ListRank[i - 1])
//                    {
//                        if (j->first != PlayerName)
//                        {
//                            return j->second;
//                        }
//                    }
//                }
//            }
//            else
//            {
//                for (auto j = ListPlayer.begin(); j != ListPlayer.end(); j++)
//                {
//                    if (j->second->getRank() == ListRank[i + 1])
//                    {
//                        if (j->first != PlayerName)
//                        {
//                            return j->second;
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
//
//// File json
//void GameDatabase::from_json(json& j, shared_ptr<Player> p)
//{
//    p->setName(j.at("Name"));
//    p->setWin(j.at("Wins"));
//    p->setDraw(j.at("Draws"));
//    p->setLose(j.at("Loses"));
//}
//
//
//void GameDatabase::recordToPlayerFile(shared_ptr<GameProperties> PlayedGame)
//{
//    int ID = PlayedGame->getIDGame();
//    string id = "ID " + to_string(ID);
//    int sizeBoard = PlayedGame->getSizeBoard();
//
//    vector<shared_ptr<PointChecked>> PointRecord = PlayedGame->getPointRecord();
//    json JsonPoint;
//    for (int i = 0; i < PointRecord.size(); i++)
//    {
//        JsonPoint[i] = { {"Row", PointRecord[i]->getRow()}, {"Col", PointRecord[i]->getCol()}, {"Checked", PointRecord[i]->getChecked()} };
//    }
//
//    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
//    // Player 1
//    fstream file1(folder + PlayedGame->getPlayer1() + ".json");
//    if (file1.fail())
//    {
//        //Create new file
//        ofstream newFile(folder + PlayedGame->getPlayer1() + ".json");
//        json j;
//        j[id] = { {"Size of Board", sizeBoard}, {"Player 1", PlayedGame->getPlayer1()}, {"Player 2", PlayedGame->getPlayer2()}, {"Winer", PlayedGame->getWiner()}, {"Point Record", JsonPoint}};
//        newFile << setw(4) << j << endl;
//    }
//    else
//    {
//        json data = json::parse(file1);
//        data[id] = { {"Size of Board", sizeBoard}, {"Player 1", PlayedGame->getPlayer1()}, {"Player 2", PlayedGame->getPlayer2()}, {"Winer", PlayedGame->getWiner()}, {"Point Record", JsonPoint} };
//        ofstream o;
//        o.open(folder + PlayedGame->getPlayer1() + ".json");
//        o << setw(4) << data << endl;
//    }
//    file1.close();
//    // Player 2
//    fstream file2(folder + PlayedGame->getPlayer2() + ".json");
//    if (file2.fail())
//    {
//        //Create new file
//        ofstream newFile(folder + PlayedGame->getPlayer2() + ".json");
//        json j;
//        j[id] = { {"Size of Board", sizeBoard}, {"Player 1", PlayedGame->getPlayer1()}, {"Player 2", PlayedGame->getPlayer2()}, {"Winer", PlayedGame->getWiner()}, {"Point Record", JsonPoint} };
//        newFile << setw(4) << j << endl;
//    }
//    else
//    {
//        json data = json::parse(file2);
//        data[id] = { {"Size of Board", sizeBoard}, {"Player 1", PlayedGame->getPlayer1()}, {"Player 2", PlayedGame->getPlayer2()}, {"Winer", PlayedGame->getWiner()}, {"Point Record", JsonPoint} };
//        ofstream o;
//        o.open(folder + PlayedGame->getPlayer2() + ".json");
//        o << setw(4) << data << endl;
//    }
//    file2.close();
//}
//
//// Get list information of played game
//map<string, shared_ptr<GameRecord>> GameDatabase::getListGamePlayed(string PlayerName)
//{
//    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
//    fstream file(folder + PlayerName + ".json");
//    map<string, shared_ptr<GameRecord>> ListGamePlayed;
//    if (file.fail())
//    {
//        return ListGamePlayed;
//    }
//    else
//    {
//        json data = json::parse(file);
//        
//        for (json::iterator i = data.begin(); i != data.end(); i++)
//        {
//            vector<shared_ptr<PointChecked>> ListPoint;
//            json JsonGame = i.value();
//            json JsonListPoint = JsonGame.at("Point Record");
//            for (int j = 0; j < JsonListPoint.size(); j++)
//            {
//                int tRow = JsonListPoint[j].at("Row");
//                int tCol = JsonListPoint[j].at("Col");
//                int checked = JsonListPoint[j].at("Checked");
//                char tChecked = checked;
//                shared_ptr<PointChecked> tPoint(new PointChecked(tRow, tCol, tChecked));
//                ListPoint.push_back(tPoint);
//            }
//            int tSizeBoard = JsonGame.at("Size of Board");
//            string tPlayer1 = JsonGame.at("Player 1");
//            string tPlayer2 = JsonGame.at("Player 2");
//            string tWiner = JsonGame.at("Winer");
//            shared_ptr<GameRecord> rGame(new GameRecord(tSizeBoard, tPlayer1, tPlayer2, tWiner, ListPoint));
//            ListGamePlayed.insert({ i.key(), rGame });
//        }
//        return ListGamePlayed;
//    }
//    file.close();
//}
//
//void GameDatabase::writeIDFile(int IDGame)
//{
//    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
//    fstream file(folder + "ID_Game" + ".ini");
//
//    if (file.fail())
//    {
//        ofstream newFile(folder + "ID_Game" + ".ini");
//        newFile << IDGame;
//        newFile.close();
//    }
//    else
//    {
//        file << IDGame;
//    }
//    file.close();
//}
//int GameDatabase::getPreIDGame()
//{
//    string folder = "C:/Users/nguye/OneDrive/Desktop/C++ FPT/Code_Examples/BT/MockC++/ServerCaro/Databases/";
//    fstream file(folder + "ID_Game" + ".ini");
//
//    if (file.fail())
//    {
//        ofstream newFile(folder + "ID_Game" + ".ini");
//        newFile << 0;
//        newFile.close();
//        return 0;
//    }
//    else
//    {
//        string ID;
//        file >> ID;
//
//        return stoi(ID);
//    }
//    file.close();
//}