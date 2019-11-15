#define PDC_DLL_BUILD 1
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include "keyInputs.h"
//#include "textBuffer.h"
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>

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


string generateBin(int n)
{
	int power = 1;
	string output;
	int mask = 1;

	if (n == 0)
	{
		return "0";
	}

	while (mask <= n)
	{
		int num = (n / mask) % 2;

		if (num == 1)
			output = "1" + output;
		else
			output = "0" + output;

		mask = pow(2, power);
		power++;
	}
	return output;
}

void recordFrequency(string text)
{
	ifstream input;
	input.open(text);
	vector<string> words;
	while (!input.eof())
	{
		string grab_word;
		getline(input, grab_word, ' ');
		words.push_back(grab_word);
	}
	input.close();
	input.open(text);
	// step 1
	unordered_map<string, int> frequencies{};
	for (auto word : words)
	{
		frequencies[word]++;
	}

	vector<string> keys{};
	for (auto kvp : frequencies)
	{
		keys.push_back(kvp.first);
	}

	for (auto key : keys)
	{
		cout << key << ": " << frequencies[key] << endl;
	}

	// step 2
	priority_queue<pair <int, string>> data;
	for (auto temp : frequencies)
	{
		data.push(make_pair(temp.second, temp.first));
	}

	//step 3
	unordered_map<string, string> frqt{};
	int counter = 0;
	for (auto binaryNum : frequencies)
	{
		frqt[data.top().second] = generateBin(counter);
		counter++;
		data.pop();
	}

	string compressedFile = text.substr(0, text.size() - 4) +
		".compressed.txt";
	string codesFile = text.substr(0, text.size() - 4) +
		".codes.txt";
	ofstream output;

	//step 4
	output.open(compressedFile);
	while (!input.eof())
	{
		string words;
		getline(input, words, ' ');
		for (auto bvalues : frqt)
		{
			output << frqt[words] + " ";
		}
	}
	output.close();
	input.close();
}

string fn = "";

int main(int argc, char* argv[])
{
	/*----------------------------------------------------------------------*
	*                     MAIN PROGRAM LOGIC GOES HERE						*
	* ----------------------------------------------------------------------*/	
	//recordFrequency("happy.txt");
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