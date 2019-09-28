<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS
=======
<<<<<<< HEAD


>>>>>>> 55d170107f74670157d15324fe559d9bc37fbaa1
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
<<<<<<< HEAD
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
	

	int ch, prev, row, col;
	prev = EOF;
	FILE* file;
	//file = "FirstNames.txt";
	int y, x;
	if (argc != 2)
	{
		printf("Using: %s <a c FirstNames.txt> \n", argv[0]);
		exit(1);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror("CANNOT OPEN INPUT FILE");
		exit(1);
	}

	getmaxyx(stdscr, row, col);
	while ((ch = fgetc(file)) != EOF)
	{
		getyx(stdscr, y, x);
		if (y == (row - 1))
		{
			printw("<- PRESS ANY KEY ->");
			getch();
			clear();
			move(0, 0);
		}
		if (prev == '/' && ch == '*')
		{
			attron(A_BOLD);
			getyx(stdscr, y, x);
			move(y, x - 1);
			printw("%c%c", '/', ch);
		}
		else
			printw("%c", ch);
		refresh();
		if (prev == '*' && ch == '/')
			attroff(A_BOLD);

		prev = ch;
		fclose(file);
	}

	/*******************************************************
					  END OF TESTING
	*********************************************************/

	/*******************************************************
					  Terminal Window
	*********************************************************/
	
=======
					  Terminal Window
	*********************************************************/
>>>>>>> 55d170107f74670157d15324fe559d9bc37fbaa1
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
<<<<<<< HEAD
=======
=======
#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#else
//Linux / MacOS includes
#include <curses.h>
#endif
#include <string>
#include <sstream>

using namespace std;

#define ctrl(x)           ((x) & 0x1f)

void draw_centered(WINDOW* win, int max_y, int max_x, string text);

int main(void)
{
	WINDOW* main_window = nullptr;
	int num_cols = 0;
	int num_rows = 0;

	//SETUP
	//initialize our window
	main_window = initscr();

	//resize our window
	resize_term(5000, 5000);
	getmaxyx(main_window, num_rows, num_cols);
	resize_term(num_rows - 1, num_cols - 1);
	getmaxyx(main_window, num_rows, num_cols);

	//turn keyboard echo
	noecho();

	cbreak();

	//turn on keypad input
	keypad(main_window, TRUE);

	//hide the cursor
	curs_set(FALSE);

	//MAIN PROGRAM LOGIC GOES HERE

	//pause for user input
	bool keep_going = true;
	while (keep_going == true)
	{
		//clear window
		wclear(main_window);

		ostringstream temp_str{};
		temp_str << "width: " << num_cols << " height: " << num_rows;
		draw_centered(main_window, num_rows, num_cols, temp_str.str().c_str());
		refresh();
		int input = wgetch(main_window);

		//Curses documentation says to use KEY_RESIZE, but you can also use
		//is_termresized.  In real life, use either/or but not both.
		if (is_termresized() == true)
		{
			resize_term(0, 0);
			getmaxyx(main_window, num_rows, num_cols);
		}
		switch (input)
		{
		case ctrl('c'):
			keep_going = false;
		case KEY_RESIZE:
			resize_term(0, 0);
			getmaxyx(main_window, num_rows, num_cols);
		}
	}
	//end curses mode
	endwin();
}

void draw_centered(WINDOW* win, int max_y, int max_x, string text)
{
	int length = text.length();
	int left_margin = (max_x - length) / 2;
	int top_margin = (max_y - 1) / 2;
	mvwprintw(win, top_margin, left_margin, text.c_str());
>>>>>>> dbd8dbc3588108dc5789a8d4cc68ee3e1186905e
>>>>>>> 55d170107f74670157d15324fe559d9bc37fbaa1
}