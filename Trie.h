#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
    TrieNode *_root = nullptr;

protected:

public:
    Trie()
    {
        _root = new TrieNode{};
    }

    virtual ~Trie()
    {
        //TODO: clean up memory
    }

	//TODO: implement
    void addWord(const string &word)
    {
		TrieNode* addingChar = _root;
	
		for (int i = 0; i < word.length(); i++)
		{
			char currentChar = word[i];
			if (addingChar->hasChild(currentChar) == true)
			{
				addingChar->setChild(currentChar, addingChar);
				addingChar = addingChar->getChild(currentChar);
			}
			addingChar->isSentinel() == true;
		}
    }

	//TODO: implement
    vector<string> search(const string &word)
    {
		TrieNode* searchingChar = _root;
		vector<string> matches;

		for (int j = 0; j < word.length(); j++)
		{
			char searchWord = word[j];
			searchingChar = searchingChar->getChild(searchWord);
		}
	
		//recursive pre-order walk of tree
		cout << searchingChar->getValue() << endl;
		for (auto child : searchingChar->getChildren())
		{
			cout << child.first << " " << child.second << endl;
		}
        return matches;
    }
};

#endif // !TRIE_H
