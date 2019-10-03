//#define _CRT_SECURE_NO_WARNINGS
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include "keyInputs.h"
#include "textBuffer.h"
#include <string>
#include <algorithm>

using namespace std;

void curses_init()
{
	initscr(); //initializing window
	noecho(); //don't echo keys
	cbreak(); //disable line buffering
	keypad(stdscr, true);
}

int main(int argc, char* argv[])
{
	/*******************************************************
						  TESTING (work in progress)
	*********************************************************/
	/*
	char message[] = "Enter a string: ";
	char str[80];
	int row, col;
	getmaxyx(stdscr, row, col);
	mvprintw(row / 2, (col - strlen(message)) / 2, "%s", message);
	getstr(str);
	mvprintw(LINES - 2, 0, "You Entered: %s", str);
	*/

	/*******************************************************
					  END OF TESTING
	*********************************************************/

	/*******************************************************
					  Terminal Window
	*********************************************************/

	string fn = "";
	keyInputs key;

	if (argc > 1)
	{
		fn = argv[1]; //set the filename
		key = keyInputs(fn);
	}
	else
	{
		key = keyInputs();
	}

	curses_init();  //initializing curses

	while (key.getMode() != 'x') // exit mode
	{
		key.updateStatus();
		key.printStatusLine();
		key.printBuff();
		int input = getch();	//blocking until input
		key.handleInput(input);
	}

	//refresh tells curses to draw everything
	refresh();

	//END OF PROGRAM
	getch();
	endwin();

}