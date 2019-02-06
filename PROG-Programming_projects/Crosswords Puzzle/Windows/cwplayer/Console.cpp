#include "Console.h"
#include <ctime>
#include <cstdlib>
#include <windows.h>


void Console::clrscr(void) {
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}


// Set text color
void Console::setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

// Set text color & background
void Console::setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
}

void Console::printLine(int color, int backgroundColor, string text) {
	cout << color << backgroundColor << text << NO_COLOR << endl;
}

void Console::printCharacter(int textColor, int bkgColor, char character) {

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	if (bkgColor == LIGHTMAGENTA)
		SetConsoleTextAttribute(hCon, textColor | BACKGROUND_BLUE | BACKGROUND_GREEN);
	else setcolor(textColor, bkgColor);

	cout << character;
	setcolor(WHITE, BLACK);

}