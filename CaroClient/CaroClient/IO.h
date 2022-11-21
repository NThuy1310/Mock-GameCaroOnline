#pragma once
#include"ConsoleSetting.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

enum ChoiceMode
{
	KEY_BOARD = 1,
	MOUSE_CLICK = 2
};

class IO
{
public:

	// Input
	static int inputLoginOrRegister();
	static string inputName();
	static int inputMenu();
	static int inputSizeBoard();
	static int inputIDGamePlayed();
	static int inputValidIndex(int);
	// Display
	static void displayPlayerInfo(string, int, int, int, int);
	static void displayGamePlayed(vector<string>);
	static void displayBoard(int, string, string);
	static void displayPointChecked(int, int, char);
};