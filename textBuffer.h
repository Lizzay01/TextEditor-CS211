#pragma once
#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include "curses.h"
#include <string>
#include <vector>

using namespace std;

class textBuffer
{
private:
public:
	textBuffer();

	vector<string> lines;

	void insertLine(string, int);
	void appendLine(string);
	void removeLine(int);
	string removeTabs(string);
};

#endif