#pragma once
#ifndef KEYINPUTS_H
#define KEYINPUTS_H

#include "curses.h"
#include "textBuffer.h"

#define CED_TITLE "TextEditor"
#define CED_VERSION "v0.1.0"

class keyInputs
{
private:
	int x, y; // x and y positions on screen
	int lowerbound; //<--*
	char mode;
	bool raiseflag; //<--*
	textBuffer* buffer;
	string status;
	string filename;
	string cmd; //<--*

	string tos(int); //<--*

	bool execCmd(); //<--*

	// cursor movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void deleteLine();	//deletes current line
	void deleteLine(int i); //deletes line <int>

	void saveFile(); //saves buffer into the file
public:
	bool upStatus; //<--*
	keyInputs();  //normal constructor
	keyInputs(string);  //constructor accepting filename

	char getMode() { return mode; }
	void handleInput(int); //handles keyboard input
	void printBuff();
	void printStatusLine(); //prints the status line
	void updateStatus(); //updates the status line (text)
};

#endif