#pragma once
#include<Windows.h>

class SettingWindow
{
public:
	SettingWindow();
	~SettingWindow();

	static void disableResizeWindow();
	static void gotoXY(int, int);
	static void textColor(int, int);
	static void setCursor(bool);
};