#pragma once
#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>
#include <vector>

using namespace std;

class textBuffer
{
public:
	textBuffer();

	vector<string> lines;

	// helper functions
	void insertLine(string, int);
	void appendLine(string);
	void removeLine(int);

	// substitutes all tabs in string for 4 spaces,
	// so that the tabs won't screw everything up
	string removeTabs(string);
};

#endif