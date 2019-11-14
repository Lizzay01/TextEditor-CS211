#include "textBuffer.h"

textBuffer::textBuffer() {}

string textBuffer::removeTabs(string line)
{
	int tab = line.find("\t"); // warning: possible loss of data
	if (tab == line.npos)
	{
		return line;
	}
	else
	{
		return removeTabs(line.replace(tab, 1, "    "));
	}
}

//helper functions
void textBuffer::insertLine(string line, int n)
{
	line = removeTabs(line);
	lines.insert(lines.begin() + n, line);
}

void textBuffer::appendLine(string line)
{
	line = removeTabs(line);
	lines.push_back(line);
}

void textBuffer::removeLine(int n)
{
	lines.erase(lines.begin() + n);
}