#include"IO.h"

int IO::inputLoginOrRegister()
{
	int chose;
	cout << "Enter your choice: " << endl;
	cout << "1. Log In " << endl;
	cout << "2. Register " << endl;
	cin >> setw(1) >> chose;

	while (!cin.good() || chose <= 0 || chose > 2)
	{
		cout << "Faulty input! Try again.." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter your choice: " << endl;
		cin >> setw(1) >> chose;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	
	return chose;
}
string IO::inputName()
{
	string Name;
	cout << "Enter your user name: " << endl;
	getline(cin >> ws, Name);
	while (Name.size() > 20)
	{
		cout << "Faulty input! User name can only contain up to 20 characters." << endl;
		cout << "Enter your user name: " << endl;
		getline(cin >> ws, Name);
	}

	return Name;
}
int IO::inputMenu()
{
	int choice;
	cout << "Enter your choice: " << endl;
	cout << "1. Player Info " << endl;
	cout << "2. New Game " << endl;
	cout << "3. List game Played " << endl;
	cout << "4. Replay game Played " << endl;
	cout << "5. Exit " << endl;
	cin >> setw(1) >> choice;

	while (!cin.good() || choice <= 0 || choice > 5)
	{
		cout << "Faulty input! Try again.." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter your choice: " << endl;
		cin >> setw(1) >> choice;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}
int IO::inputSizeBoard()
{
	int sizeBoard = 0;
	cout << "Enter size of board: " << endl;
	cin >> sizeBoard;
	while (!cin.good())
	{
		cout << "Faulty input! Try again.." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter your choice: " << endl;
		cin >> setw(1) >> sizeBoard;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return sizeBoard;
}
int IO::inputIDGamePlayed()
{
	int ID = 0;
	cout << "Enter ID you want to replay: " << endl;
	cin >> ID;
	while (!cin.good())
	{
		cout << "Faulty input! Try again.." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter your choice: " << endl;
		cin >> setw(1) >> ID;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return ID;
}
int IO::inputValidIndex(int SizeBoard)
{
	int num;
	cin >> setw(1) >> num;

	while (!cin.good() || num < 0)
	{
		cout << "Faulty input!. You must enter a positive integer." << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "Try again: " << endl;
		cin >> setw(1) >> num;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	while (num < 0 || num > SizeBoard)
	{
		cout << "Faulty input!. You must enter a number from 0 to " << SizeBoard << endl;
		cout << "Try again: " << endl;
		cin >> setw(1) >> num;
	}
	return num;
}


void IO::displayPlayerInfo(string Name, int Wins, int Loses, int Draws, int Rank)
{
	cout << "* Player name: " << Name << endl;
	cout << "* Number of win game: " << Wins << endl;
	cout << "* Number of draw game: " << Loses << endl;
	cout << "* Number of lose game: " << Draws << endl;
	cout << "* Player Rank: " << Rank << endl;
}
void IO::displayGamePlayed(vector<string> ListData)
{
	system("cls");
	int IDGame = stoi(ListData[3]);
	int SizeBoard = stoi(ListData[4]);
	string Player1 = ListData[5];
	string Player2 = ListData[6];
	string Winer = ListData[7];
	displayBoard(SizeBoard, Player1, Player2);
	SettingWindow::gotoXY(0, 2 * SizeBoard + 4);
	SettingWindow::textColor(0, 14);
	cout << "ID = " << IDGame;
	for (int i = 8; i < ListData.size(); i += 3)
	{
		int Row = (int)(char)stoi(ListData[i]) - 48;
		int Col = (int)(char)stoi(ListData[i + 1]) - 48;
		const char* tempChecked = ListData[i+2].c_str();
		char Checked = *tempChecked;
		displayPointChecked(Row, Col, Checked);
		
		Sleep(1000);
	}
	SettingWindow::gotoXY(0, 2 * SizeBoard + 5);
	SettingWindow::textColor(0, 14);
	cout << "Winner: " << Winer << endl;

	system("pause");
}

void IO::displayBoard(int SizeBoard, string Name1, string Name2)
{
	SettingWindow::textColor(0, 10); //Green
	SettingWindow::gotoXY(0, 0);
	cout << "Player 1 <X>: " << Name1 << " - Player 2 <O>: " << Name2;
	for (int i = 2; i < (2 * SizeBoard + 2); i++)
	{
		for (int j = 0; j < 4 * SizeBoard - 1; j++)
		{
			SettingWindow::gotoXY(j, i);
			if (i % 2 == 0)
			{
				if ((j + 1) % 4 == 0)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			else
			{
				cout << "-";
			}
		}
	}
}
void IO::displayPointChecked(int Row, int Col, char TypeChecked)
{
	int posXChecked = 4 * Col + 1;
	int posYChecked = 2 * Row + 2;
	if (TypeChecked == 'X')
	{
		SettingWindow::textColor(0, 12); // Red
		SettingWindow::gotoXY(posXChecked, posYChecked);
		cout << TypeChecked;
	}
	else if (TypeChecked == 'O')
	{
		SettingWindow::textColor(0, 11); // Aqua
		SettingWindow::gotoXY(posXChecked, posYChecked);
		cout << TypeChecked;
	}
}