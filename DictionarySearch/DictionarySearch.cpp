// DictionarySearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//	Ng Hsin Kai S10179111D
//	Jonathan Tan Jie Kai S10178707B
//	Wong Shin Feng S10179994
//	The program will tell the user what letter is accidentally inserted into the word.

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Trie.h"

using namespace std;

//constant variables
const string inputOptions[5] = { "1) Spell check a word", "2) Spell check a file", "3) Add a new Word", "4) Save the dictionary", "5) Display all words in dictionary starting with..." };
string filename = "RandomWords100.txt";
string Reason;


//show options menu
//input : &answer
//output : menu printed
void showInputs(int &answer) {
	//loop through array and print values
	cout << "\n" << string(55,'=') << endl;
	for(string options : inputOptions)
	{
		cout << options << endl;
	}
	cout << string(55, '=') << endl;
	//ask for input
	cout << endl << "Choose an option: ";
	//dereference input
	cin >> answer;

}

//get the words from the textfile and add the words into the trie
//inputs : filename and &trie
//output : ptrie with data
void getwords(string fileName, Trie &trie) {
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//insert line of word into tree
			trie.insert(line);

		}
		myfile.close();
	}
}

//Advanced Feature
//inputs : enteredWord and &trie
//output : show the reason of the error if any
void checkError(string enteredWord, Trie &trie)
{
	transform(enteredWord.begin(), enteredWord.end(), enteredWord.begin(), ::tolower);
	//Counter to check type of error
	int r = 0;
	//Checks for insertion error
	for (int i = 0; i < enteredWord.length(); i++)
	{
		string x = enteredWord;
		x.erase(x.begin() + i);
		if (trie.search(x) == true)
		{
			Reason = "=== Insertion error of letter '";
			Reason += enteredWord[i];
			Reason += "' === \n";
			r = 1; // States that the error is an insertion error
			break;
		}
	}
	if (r == 0)
	{
		for (int i = 0; i < enteredWord.length() - 1; i++)
		{
			string y = enteredWord;
			char swap1 = enteredWord[i];
			char swap2 = enteredWord[i + 1];
			y[i] = swap2;
			y[i + 1] = swap1;
			if (trie.search(y) == true)
			{
				
				Reason = "=== Transposition Error === \n";
				r = 2;
				break;
			}
		}
	}
}

//search for the word that is entered
//inputs : enteredWord and &trie
//output : print if word is in file
void searchWord(string enteredWord, Trie& trie) {
	cout << "Enter a word to check spelling: ";
	cin >> enteredWord;
	//make word lowercase		
	cout << "\n";
	transform(enteredWord.begin(), enteredWord.end(), enteredWord.begin(), ::tolower);
	cout << (trie.search(enteredWord) ? "This word is spelt correctly!" : "There is no such word in the dictionary!") << endl;
	// Advanced features, error checking
	if (trie.search(enteredWord) == false)
	{
		checkError(enteredWord, trie);
		cout << Reason;
		Reason = "";
	}
}

//Insert a new word into the trie
//inputs : enteredWord and &trie
//output : insert word into trie and show success 
void insertWord(string enteredWord, Trie& trie) {
	cout << "Enter a word to Add into the dictionary: ";
	cin >> enteredWord;
	cout << "\n";
	//make word lowercase		
	transform(enteredWord.begin(), enteredWord.end(), enteredWord.begin(), ::tolower);
	cout << (trie.insert(enteredWord) ? "The word has been added successfully!" : "The addition of the word has failed! Please try again.");
	cout << "\n";
}

//save the new trie into textfile
//inputs : List of all words
//output : save trie to dictionary and print success
void saveDictionary(List newlist) {
	std::ofstream outfile;
	outfile.open(filename);

	for (int i = 0; i < newlist.getLength(); i++)
	{
		
		outfile << newlist.get(i) << endl;
	}

	outfile.close();
	cout << "Dictionary has been saved!\n";
}

//check spelling of a file against another
//inputs : trie
//output : print all mispelt/missing words with error reason
void checkFile(Trie trie) {
	string fileName2;
	cout << "Enter file name for spell check : ";
	cin >> fileName2;
	cout << "\n";
	string line, finalText;
	ifstream myfile(fileName2);
	int count = 0;
	if (myfile.is_open())
	{
		cout.width(15); cout << right << "Word\t:   ";
		cout << "Reason\n";
		while (getline(myfile, line))
		{ 
			//check for similar word
			if (trie.search(line) == false)
			{
				count++;
				checkError(line, trie);
				if (Reason.length() > 0)
				{
					cout.width(15); cout << right << line << "\t:   ";
					cout << Reason;
					//finalText += line + "\t" + Reason ;
				}
				else
				{
					cout.width(15); cout << right << line << "\t:   \n";
				}
					
				Reason = "";
			}

		}
		myfile.close();
	}
	/*if (count>0)
	{
		cout << "The words that are mispelt: " << endl << finalText << endl;
	}*/
}

//check words starting with a certain prefix
//inputs : prefix, newlist and trie
//outputs : show all words that start with the entered prefix
void checkForPrefix(string prefix, List newlist, Trie trie)
{
	string enteredWord;
	//ask for prefix input
	cout << "Enter your prefix to search: ";
	cin >> enteredWord;
	trie.traverse(prefix, *trie.head, newlist, enteredWord, 0);
	cout << "\n";
	cout.width(15); cout << right << "The words beginning with " << enteredWord << " are:\n";
	newlist.print();
	
}

int main()
{
	//variables
	int answer;

    std::cout << "Hello World!\n";	
	//Make a trie object
	Trie trie = Trie();

	//get words from file
	/*string fileName;
	cout << "what file do you want to read from?";
	cin >> fileName;
	getwords(fileName);
	*/

	//get words from default file
	getwords(filename, trie);
	bool continueRunning = true;
	while (continueRunning) {
		//show options menu with reference to answer
		showInputs(answer);

		string enteredWord;
		string prefix = "";

		List newlist = List();

		vector<string>wordsList;
		switch (answer)
		{
		case 1:
			searchWord(enteredWord, trie);

			break;
		case 2:
			checkFile(trie);
			break;
		case 3:
			insertWord(enteredWord, trie);
			break;
		case 4:
			trie.traverse(prefix, *trie.head, newlist);
			saveDictionary(newlist);
			break;
		case 5:
			//ask for starting alpha
			checkForPrefix(prefix, newlist, trie);
			//filter(wordsList, prefix, trie);
			break;
		default:
			continueRunning = false;
			break;
		}
	}
}
