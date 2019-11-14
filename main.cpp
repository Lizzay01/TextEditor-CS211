#define PDC_DLL_BUILD 1
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include "keyInputs.h"
//#include "textBuffer.h"
#include <string>
#include <cstdlib>
#include <algorithm>


using namespace std;

void curses_init()
{
	/*******************************************************
					  Terminal Window
	*********************************************************/
	WINDOW* main_window = nullptr;
	/*int num_cols = 0;
	int num_rows = 0;*/

	//initializing our window
	//main_window = initscr();
	//resize_term(5000, 5000); <-- gets full screen
	//resize window
	//getmaxyx(main_window, num_rows, num_cols);
	//resize_term(num_rows - 1, num_cols - 1);
	//getmaxyx(main_window, num_rows, num_cols);

	initscr(); //initializing window
	noecho(); //don't echo keys
	cbreak(); //disable line buffering
	keypad(stdscr, true);
	//scrollok(main_window, TRUE);
}

string fn = "";

int main(int argc, char* argv[])
{
	/*----------------------------------------------------------------------*
	*                     MAIN PROGRAM LOGIC GOES HERE						*
	* ----------------------------------------------------------------------*/	
	
	keyInputs key;
	//initializing filename
	if (argc > 1)
	{
		
		fn = string(argv[1]); 
		key = keyInputs(fn);
	}
	else
	{
		key = keyInputs();
	}
	
	curses_init();

	while (key.getMode() != 'x') // exit mode
	{
		if (key.upStatus)
			key.updateStatus();
		key.printStatusLine();
		key.printBuff();
		int input = getch();	//blocking until input
		key.handleInput(input);
	}

	//refresh tells curses to draw everything
	refresh();

	/*----------------------------------------------------------------------*
	*                         END OF PROGRAM								*
	* ----------------------------------------------------------------------*/
	getch();
	endwin();
}