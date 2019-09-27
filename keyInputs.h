#pragma once
#ifndef KEYINPUTS_H
#define KEYINPUTS_H

#include "curses.h"
#include "textBuffer.h"

class keyInputs
{
private:
	int x, y; // x and y positions on screen
	char mode;
	textBuffer* buffer;
	string status, filename;

	// cursor movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void deleteLine();	//deletes current line
	void deleteLine(int); //deletes line <int>

	void saveFile(); //saves buffer into the file
public:
	keyInputs();  //normal constructor
	keyInputs(string);  //constructor accepting filename

	char getMode() { return mode; }
	void handleInput(int); //handles keyboard input
	void printBuff();
	void printStatusLine(); //prints the status line
	void updateStatus(); //updates the status line (text)
};

#endif