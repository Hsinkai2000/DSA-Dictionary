#include "pch.h"
#include "List.h"


List::List()
{
	firstNode = NULL;
	size = 0;
}


List::~List()
{
}

bool List::add(ItemType item)
{
	ListNode *newNode = new ListNode;
	newNode->item = item;
	newNode->next = NULL;
	ListNode *temp = firstNode;
	if (size == 0)
	{
		firstNode = newNode;
	}
	else {
		for (int i = 1; i < size; i++)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}

	size++;
	return true;
}

int List::getLength()
{
	return size;
}
ItemType List::get(int index)
{
	ListNode *temp = firstNode;
	ItemType itemString = "";
	for (int i = 0; i < index - 1; i++)
	{
		temp = temp->next;
	}
	itemString = temp->item;

	return itemString;
}


void List::print()
{
	ListNode *temp = firstNode;
	cout.width(15); cout << right << "Word : " << temp->item << '\n';
	for (int i = 1; i < size; i++)
	{
		temp = temp->next;
		cout.width(15); cout << right << "Word : " << temp->item << '\n';
	}
	cout << "\n";
}
