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

/*******************************************************
					 Milestone 6
*********************************************************/
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
		if (grab_word == " ")
		{
			continue;
		}
		for (auto ch : grab_word)
		{
			if (ch == '\n')
			{
				grab_word = grab_word.substr(0, grab_word.length()-1);
			}
		}
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
		if (words == " ")
		{
			continue;
		}
		for (auto ch : words)
		{
			if (ch == '\n')
			{
				words = words.substr(0, words.length() - 1);
			}
		}
		for (auto bvalues : frqt)
		{
			output << frqt[words] << " ";
		}
	}
	output.close();
	input.close();

	input.open(text);
	output.open(codesFile);
	string wordss;
	for (auto otherValues : frqt)
	{
		output << otherValues.first << ": "
			<< otherValues.second << "\n";
	}
	output.close();
	input.close();
}
/*******************************************************
					 Milestone 6 - END
*********************************************************/


/*******************************************************
					 Milestone 7
*********************************************************/
//sorting options: INSERTION, SELECTION, BUBBLE, AND QUICK SORT 

//void bubbleSort(int* numbers, int size)
//{
//	for (int i = 0; i < size - 1; i++)
//	{
//		for (int j = 0; j < size - i - 1; j++)
//		{
//			if (numbers[j] > numbers[j + 1])
//			{
//				int temp = numbers[j];
//				numbers[j] = numbers[j + 1];
//				numbers[j + 1] = temp;
//			}
//		}
//	}
//}

//void sortingOptions()
//{
//	//int size;
//	//vector<int> nums;
//
//	int select;
//	cout << "Sorting Options Menu" << endl;
//	cin >> select;
//	if (select == 1)
//	{
//		//bubbleSort(nums, size);
//	}
//	else if (select == 2)
//	{
//		//insertionSort();
//	}
//	else if (select == 3)
//	{
//		//selectionSort();
//	}
//	else if (select == 4)
//	{
//		//quickSort();
//	}
//	else
//	{
//		cout << "Exiting Program" << endl;
//		exit(0);
//	}
//}
/*******************************************************
					 Milestone 7 - END
*********************************************************/

string fn = "";

int main(int argc, char* argv[])
{
	/*----------------------------------------------------------------------*
	*                     MAIN PROGRAM LOGIC GOES HERE						*
	* ----------------------------------------------------------------------*/	

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
	recordFrequency("happy.txt"); //milestone 6

	while (key.getMode() != 'x') // exit mode
	{
		if (key.upStatus)
			key.updateStatus();
		key.printStatusLine();
		key.printBuff();
		int input = getch();	//blocking until input
		key.handleInput(input);
	}

	//recordFrequency("happy.txt"); //milestone 6
	
    //refresh tells curses to draw everything
	refresh();

	/*----------------------------------------------------------------------*
	*                         END OF PROGRAM								*
	* ----------------------------------------------------------------------*/
	getch();
	endwin();
}