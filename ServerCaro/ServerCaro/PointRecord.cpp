#include"PointRecord.h"

PointChecked::PointChecked()
{
	//
}
PointChecked::PointChecked(int Row, int Col, char Checked)
{
	this->Row = Row;
	this->Col = Col;
	this->Checked = Checked;
}
PointChecked::~PointChecked()
{
	//
}

void PointChecked::setRow(int Row)
{
	this->Row = Row;
}
void PointChecked::setCol(int Col)
{
	this->Col = Col;
}
void PointChecked::setChecked(char Checked)
{
	this->Checked = Checked;
}

int PointChecked::getRow()
{
	return Row;
}
int PointChecked::getCol()
{
	return Col;
}
char PointChecked::getChecked()
{
	return Checked;
}