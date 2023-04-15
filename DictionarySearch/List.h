#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class List
{
private:
	struct ListNode
	{
		ItemType item;	// item
		ListNode     *next;	// pointer pointing to next item
	};
	ListNode *firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	List();

	// destructor
	~List();

	// add an item to the back of the list (append)
	//inputs : item to be added
	//output : item is added to the linked list
	bool add(ItemType item);

	// get an item at a specified position of the list (retrieve)
	//inputs : index of item trying to obtain
	//outputs : return the value of the position(index)
	ItemType get(int index);

	//get length of the linked list
	//output : return the length of the linked list
	int getLength();
	
	// display all the items in the list
	//output : prints the values in the linked list one by one
	void print();
};
