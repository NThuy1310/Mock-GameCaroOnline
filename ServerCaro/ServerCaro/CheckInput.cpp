#include"CheckInput.h"


CheckInput::CheckInput()
{
	//
}
CheckInput::~CheckInput()
{
	//
}

bool CheckInput::checkInvalidPoint(int Row, int Col, shared_ptr<GameProperties> GamePlaying)
{
	vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
	if (BoardCheck[Row][Col] != ' ')
	{
		return true;
	}
	return false;

	//int SizeBoard = GamePlaying->getSizeBoard();
	//vector<vector<char>> BoardCheck = GamePlaying->getPointOfBoard();
	//if (Row < 2 || Row >((2 * SizeBoard) + 2) || (Col > ((4 * SizeBoard) - 1)))
	//{
	//	return true;
	//}
	//else if ((Col + 1) % 4 == 0)
	//{
	//	return true;
	//}
	//else if (BoardCheck[(Row - 2) / 2][(Col + 1) / 4] != ' ')
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}