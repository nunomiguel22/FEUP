#pragma once 

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define COUT_SIZE 56

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define NO_COLOR 15

// BACKGROUND COLOR CODES
#define BLACK_B 0
#define RED_B 4
#define GREEN_B 2
#define YELLOW_B 14
#define BLUE_B 1
#define MAGENTA_B 5
#define CYAN_B 3
#define WHITE_B 15


class Console {
public:
	void clrscr(void);
	void setcolor(unsigned int color);
	void setcolor(unsigned int color, unsigned int background_color);
	void printLine(int color, int backgroundColor, string text);
	void printCharacter(int textColor, int bkgColor, char character);
};


