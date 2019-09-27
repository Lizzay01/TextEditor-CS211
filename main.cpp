

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