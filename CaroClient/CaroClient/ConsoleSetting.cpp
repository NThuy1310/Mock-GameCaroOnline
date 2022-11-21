#include"ConsoleSetting.h"

SettingWindow::SettingWindow()
{
	//
}
SettingWindow::~SettingWindow()
{
	//
}
void SettingWindow::disableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void SettingWindow::gotoXY(int PosX, int PosY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = PosX;
	Position.Y = PosY;

	SetConsoleCursorPosition(hStdout, Position);
}
void SettingWindow::textColor(int BackgoundColor, int TextColor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = BackgoundColor * 16 + TextColor;
	SetConsoleTextAttribute(hStdout, color_code);
}
void SettingWindow::setCursor(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}