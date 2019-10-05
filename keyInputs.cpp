#include "keyInputs.h"
#include "curses.h"
#include <fstream>
#include <iostream>
#include <sstream>

keyInputs::keyInputs()
{
	x = 0;
	y = 0;
	mode ='n';
	status = "Normal Mode";
	filename = "untitled";

	//Initializes buffer anad appends line
	// to prevent seg. faults

	buffer = new textBuffer();
	buffer->appendLine("");
}

keyInputs::keyInputs(string fn)
{
	x = 0;
	y = 0;
	mode = 'n';
	filename = fn;

	buffer = new textBuffer();

	ifstream infile(fn.c_str());
	if (infile.is_open())
	{
		while (infile.good()) // took off "!"
		{
			string temp;
			getline(infile, temp);
			buffer->appendLine(temp);
		}
	}
	else
	{
		cout << "Cannot open: " << fn << "'\n";
		buffer->appendLine("");  // has items but is not displaying  right
	}
}

//string keyInputs::to_string(int i)
//{
//	stringstream ss;
//	ss << i;
//	return ss.str();
//}

void keyInputs::updateStatus()
{
	switch (mode)
	{
	case 'n':
		//normal mode
		status = "Normal Mode";
		break;
	case 'i':
		//insert mode
		status = "Insert Mode";
		break;
	case 'x':
		//exit mode
		status = "Exiting";
		break;
	}
	status += "\tCOL: " + std::to_string(x) + "\tROW: " + std::to_string(y); 
}

void keyInputs::handleInput(int c)
{
	switch (c)
	{
	case KEY_LEFT:
		moveLeft();
		return;
	case KEY_RIGHT:
		moveRight();
		return;
	case KEY_UP:
		moveUp();
		return;
	case KEY_DOWN:
		moveDown();
		return;
	}
	switch (mode)
	{
	case 'n':
		switch (c)
		{
		case 'x':
			// Press 'x' to exit
			mode = 'x';
			break;
		case 'i':
			// Press 'i' to enter insert mode
			mode = 'i';
			break;
		case 's':
			// Press 's' to save the current file
			saveFile();
			break;
		}
		break;
	case 'i':
		switch (c)
		{
		case 27:
			// The Escape/Alt key
			mode = 'n';
			break;
		case 127:
		case KEY_BACKSPACE:
			// The Backspace key
			if (x == 0 && y > 0)
			{
				x = buffer->lines[y - 1].length(); //overflow??
				// Bring the line down
				buffer->lines[y - 1] += buffer->lines[y]; // overflow??
				// Delete the current line
				deleteLine();
				moveUp();
			}
			else
			{
				// Removes a character
				buffer->lines[y].erase(--x, 1);
			}
			break;
		case KEY_DC:
			// The Delete key
			if (x == buffer->lines[y].length() && y != buffer->lines.size() - 1)
			{
				// Bring the line down
				buffer->lines[y] += buffer->lines[y + 1]; // overflow??
				// Delete the line
				deleteLine(y + 1);
			}
			else
			{
				buffer->lines[y].erase(x, 1);
			}
			break;
		case KEY_ENTER:
		case 10:
			// The Enter key
			// Bring the rest of the line down
			if (x < buffer->lines[y].length())
			{
				// Put the rest of the line on a new line
				buffer->insertLine(buffer->lines[y].substr(x, buffer->lines[y].length() - x), y + 1);
				// Remove that part of the line
				buffer->lines[y].erase(x, buffer->lines[y].length() - x);
			}
			else
			{
				buffer->insertLine("", y + 1);
			}
			x = 0;
			moveDown();
			break;
		case KEY_BTAB:
		case KEY_CTAB:
		case KEY_STAB:
		case KEY_CATAB:
		case 9:
			// The Tab key
			buffer->lines[y].insert(x, 4, ' ');
			x += 4;
			break;
		default:
			// Any other character
			buffer->lines[y].insert(x, 1, char(c));
			x++;
			break;
		}
		break;
	}
}

void keyInputs::moveLeft()
{
	if (x - 1 >= 0)
	{
		x--;
		move(y, x);
	}
}

void keyInputs::moveRight()
{
	if (x + 1 < COLS && x + 1 <= buffer->lines[y].length()) // overflow?? fix-------
	{
		x++;
		move(y, x);
	}
}

void keyInputs::moveUp()
{
	if (y - 1 >= 0)
		y--;
	if (x >= buffer->lines[y].length())
		x = buffer->lines[y].length(); //fix?
	move(y, x);
}

void keyInputs::moveDown()
{
	if (y + 1 < LINES - 1 && y + 1 < buffer->lines.size()) // overflow?
		y++;
	if (x >= buffer->lines[y].length())
		x = buffer->lines[y].length(); // fix/change?
	move(y, x);
}

void keyInputs::printBuff()
{
	for (int i = 0; i < LINES - 1; i++)
	{
		if (i >= buffer->lines.size())
		{
			move(i, 0);
			clrtoeol();
		}
		else
		{
			mvprintw(i, 0, buffer->lines[i].c_str());
		}
		clrtoeol();
	}
	move(y, x);
}

void keyInputs::printStatusLine()
{
	attron(A_REVERSE);
	mvprintw(LINES - 1, 0, status.c_str());
	clrtoeol();
	attroff(A_REVERSE);

	// manipulate in order to display the file

}

void keyInputs::deleteLine()
{
	buffer->removeLine(y);
}

void keyInputs::deleteLine(int i)
{
	buffer->removeLine(i);
}

void keyInputs::saveFile()
{
	if (filename == "")
	{
		//setting filename to untitled
		filename = "untitled";
	}

	ofstream f(filename.c_str());
	if (f.is_open())
	{
		for (int i = 0; i < buffer->lines.size(); i++)
		{
			f << buffer->lines[i] << endl;
		}
		status = "Saved to file!";
	}
	else
	{
		status = "ERROR: Cannot open file for writing!";
	}
	f.close();
}