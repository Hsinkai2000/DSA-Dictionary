#include "pch.h"
#include "Trie.h"
#include <iostream>
Trie::Trie()
{
}


Trie::~Trie()
{
}

bool Trie::insert(string word)
{
	Node *current = head;
	//Loop through letters of word 
	//cout << word << "\n";
	for (int i = 0; i < word.length(); i++)
	{
		//find the index of alpha from A
		int letter = (int)word[i] - (int)'a';
		//cout << letter << "\n";
		//check for empty value in place of letter
		if (current->nextAlpha[letter] == NULL)
		{
			//create a new node at that location
			current->nextAlpha[letter] = new Node();
			
		}
		//proceed to next alpha node
		current = current->nextAlpha[letter];

	}
	current->is_end = true;
	return true;
}

bool Trie::search(string word)
{
	Node* current = head;
	//Loop through letters of word
	for (int i = 0; i < word.length(); i++)
	{
		//find the index of alpha from A
		int letter = (int)word[i] - (int)'a';
		//check for empty value in place of letter
		if (current->nextAlpha[letter] == NULL)
		{
			//return false if no next letter found
			return false;
		}
		else
		{
			//proceed to next alpha node
			current = current->nextAlpha[letter];
		}
	}
	//if reach the end, return current->isend
	return current->is_end;
}


void Trie::traverse(string& prefix, Node& node, List& newlist) {
	//check if node is last letter of word
	if (node.is_end)
	{
		newlist.add(prefix);
	}
	//loop through alphabet char
	for (char index = 0; index < 26; ++index) {
		char next = 'a' + index;
		Node* pChild = node.nextAlpha[index];
		//check if node is not empty
		if (pChild) {
			//append next letter to prefix
			prefix.push_back(next);
			//Carry on with next possible letter
			traverse(prefix, *pChild, newlist);
			prefix.pop_back();
		}
	}
}

void Trie::traverse(string& prefix, Node& node, List& newList, string enteredPrefix, int counter) {
	Node* tempNode = &node;
	if (node.is_end)
	{
		newList.add(prefix);
	}
	//check for prefixes and traverse through the trie
	if (counter < enteredPrefix.length())
	{
		int letter = (int)enteredPrefix[counter] - (int)'a';
		tempNode = node.nextAlpha[letter];
		if (tempNode)
		{
			prefix.push_back(enteredPrefix[counter]);
			counter++;
			traverse(prefix, *tempNode, newList, enteredPrefix, counter);
		}
		else {
			cout << "No such word\n";
		}
	}
	else
	{
		for (char index = 0; index < 26; ++index) {
			char next = 'a' + index;
			Node* pChild = node.nextAlpha[index];
			//check if node is not empty
			if (pChild) {
				//append next letter to prefix
				prefix.push_back(next);
				//Carry on with next possible letter
				traverse(prefix, *pChild, newList, enteredPrefix, counter);
				prefix.pop_back();
			}
		}
	}
	
}


