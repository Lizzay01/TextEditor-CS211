#include "keyInputs.h"
#include <fstream>
#include <iostream>
#include <sstream>

keyInputs::keyInputs(string fn)
{
	x = 0;
	y = 0;
	mode = 'n';
	cmd = ""; //<--*
	lowerbound = 0; //<--*
	raiseflag = false; //<--*
	upStatus = true; //<--*
	status = "Normal Mode"; //<--*
	buffer = new textBuffer();
	filename = fn;

	// reads from file if exists
	ifstream infile(fn.c_str());
	if (infile.is_open())
	{
		while(!infile.eof())//while (infile.good()) // had it inverted fix ---
		{
			string temp;
			getline(infile, temp);
			buffer->appendLine(temp);
		}
	}
	else
	{
		cerr << "Cannot open: " << fn << endl;
		buffer->appendLine(""); // has items but is not displaying 
	}
	infile.close();
}

keyInputs::keyInputs()
{
	// for a new file
	x = 0;
	y = 0;
	mode = 'n';
	cmd = ""; //<--*
	upStatus = true; //<--*
	raiseflag = false; //<--*
	status = "Normal Mode";
	lowerbound = 0; //<--*
	filename = "";
	buffer = new textBuffer();
	buffer->appendLine("");
}

void keyInputs::updateStatus()
{
	switch (mode)
	{
	case 'n':
		//normal mode
		if (cmd.empty()) //<--*
			status = string(CED_TITLE) + " " + string(CED_VERSION);
		else
			status = cmd;
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
	status += "\tCOL: " + tos(x) + "\tROW: " + tos(lowerbound); //<--* 
}

void keyInputs::handleInput(int c)
{
	upStatus = true; //<--*
	
	switch (mode)
	{
	case 'n':
		//switch (c)
		//{
		//case 'x':
		//	// Press 'x' to exit
		//	mode = 'x';
		//	break;
		//case 'i':
		//	// Press 'i' to enter insert mode
		//	mode = 'i';
		//	break;
		//case 's':
		//	// Press 's' to save the current file
		//	saveFile();
		//	break;
		//}
		//break;
		switch (c)
		{
		case KEY_LEFT:
			moveLeft();
			break; //<--*
		case KEY_RIGHT:
			moveRight();
			break; //<--*
		case KEY_UP:
			moveUp();
			break; //<--*
		case KEY_DOWN:
			moveDown();
			break; //<--*
		case KEY_ENTER:
		case 10:
			//execute command
			execCmd();
			break;
		case 27:
			// escape/alt key; clears command
			cmd.clear();
			break;
		case 127:
		case KEY_BACKSPACE:
		case KEY_DC:
			if (!cmd.empty())
				cmd.erase(cmd.length() - 1, 1);
			break;
		default:
			cmd += string(1, char(c));
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
				x = buffer->lines[y - 1].length(); // overflow?
				// Bring the line down
				buffer->lines[y - 1] += buffer->lines[y]; // overflow?
				// Delete the current line
				deleteLine();
				moveUp();
			}
			else if(x > 0)
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
				buffer->lines[y] += buffer->lines[y + 1]; // overflow?
				// Delete the line
				deleteLine(y + 1);
			}
			else
			{
				buffer->lines[y].erase(x, 1);
			}
			break;
		case KEY_LEFT:
			moveLeft();
			break; //<--*
		case KEY_RIGHT:
			moveRight();
			break; //<--*
		case KEY_UP:
			moveUp();
			break; //<--*
		case KEY_DOWN:
			moveDown();
			break; //<--*
		case KEY_ENTER:
		case 10:
			// Bring the rest of the line down
			if (x < buffer->lines[y + lowerbound].length() - 1)
			{
				// Put the rest of the line on a new line
				buffer->insertLine(buffer->lines[y + lowerbound].substr
				(x, buffer->lines[y + lowerbound].length() - x), y + 1);
				// Remove that part of the line
				buffer->lines[y + lowerbound].erase(x, buffer->lines[y + lowerbound].length() - x);
			}
			else
			{
				buffer->insertLine("", y + lowerbound + 1);
			}
			//x = 0;
			moveDown();
			break;
		case KEY_BTAB:
		case KEY_CTAB:
		case KEY_STAB:
		case KEY_CATAB:
		case 9:
			// The Tab key
			buffer->lines[y + lowerbound].insert(x, 4, ' ');
			x += 4;
			break;
		default:
			// Any other character
			buffer->lines[y + lowerbound].insert(x, 1, char(c));
			x++;
			break;
		}
		break;
	default:;
	}
}

void keyInputs::deleteLine()
{
	buffer->removeLine(y);
}

void keyInputs::deleteLine(int i)
{
	buffer->removeLine(i);
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
	if (x + 1 < COLS && x + 1 <= buffer->lines[y].length()) // overflow?
	{
		x++;
		move(y, x);
	}
}

void keyInputs::moveUp()
{
	if (y - 1 >= 0)
	{
		y--;
	}
	else if (y - 1 < 0 && lowerbound > 0)
	{
		lowerbound--;
	}
	if (x >= buffer->lines[y].length())
		x = buffer->lines[y].length(); 
	move(y, x);
}

void keyInputs::moveDown()
{
	if (y + 1 < LINES - 1 && y + 1 < buffer->lines.size()) // overflow?
	{
		y++;
	}
	else if (lowerbound + y < buffer->lines.size())
	{
		raiseflag = true;
		lowerbound++;
	}
	if (x >= buffer->lines[y].length())
		x = buffer->lines[y].length(); 
	move(y, x);
}

void keyInputs::printBuff()
{
	int lc = 0; // line count
	for (int i = lowerbound; lc < LINES - 1; i++)
	{
		if (i >= buffer->lines.size())
		{
			//move(i, 0);
			//clrtoeol();
		}
		else
		{
			mvprintw(lc, 0, buffer->lines[i].c_str());
		}
		clrtoeol();
		lc++;
	}
	move(y, x);
}

void keyInputs::printStatusLine()
{
	if (raiseflag)
		attron(A_BOLD);
	attron(A_REVERSE);
	mvprintw(LINES - 1, 0, status.c_str());
	clrtoeol();
	if (raiseflag)
		attroff(A_BOLD);
	attroff(A_REVERSE);
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

string keyInputs::tos(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

bool keyInputs::execCmd()
{
	if (cmd == "i")
		mode = 'i';
	else if (cmd == "x")
		mode = 'x';
	else if (cmd == "s")
	{
		upStatus = false;
		saveFile();
	}

	cmd = ""; //reset command buffer
	return true; // returns if command has executed successfully
}