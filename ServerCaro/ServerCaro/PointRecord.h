#pragma once
#include<string>

using namespace std;

class PointChecked
{
private:
	int Row;
	int Col;
	char Checked;
public:
	PointChecked();
	PointChecked(int, int, char);
	~PointChecked();

	void setRow(int);
	void setCol(int);
	void setChecked(char);

	int getRow();
	int getCol();
	char getChecked();
};