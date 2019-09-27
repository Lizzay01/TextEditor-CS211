#define _CRT_SECURE_NO_WARNINGS
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