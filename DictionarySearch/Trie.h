#include "Node.h"
#include <string>
#include <vector>
#include "pch.h"
#include "List.h"

using namespace std;
class Trie
{	
public:
	Node* head = new Node();
	Trie();
	~Trie();

	//insert a new word
	//input : word to be inserted into the trie
	//output : word added to trie
	bool insert(string word);

	//search for an existing word
	//input : word to search
	//output : show if word is available in the file
	bool search(string word);

	//traverse the trie and put all words into a vector (in order)
	//inputs : prefix,node, newlist, (enteredprefix,counter)
	//outputs : all words will be added into the List/words beginning with the prefix will be added into the list
	void traverse(string& prefix, Node& node, List& newlist);
	void traverse(string& prefix, Node& node, List& newList, string enteredPrefix, int counter);
};

