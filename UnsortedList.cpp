/*
 *  UnsortedList.cpp
 */

#include "UnsortedList.h"

UnsortedList::UnsortedList()
{
	length = 0;
	listData = NULL;
	currentPos = NULL;
}

/*UnsortedList::~UnsortedList()
{
	node* ptr;
	while (listData!=NULL) 
	{
		ptr = listData->next;
		delete listData;
		listData = ptr;
		length--;
		
	}
}*/

void UnsortedList::MakeEmpty()
{
	node* ptr;
	while (length > 0) 
	{
		ptr = listData->next;
		delete listData->nodes;
		delete listData;
		listData = ptr;
		length--;
		
	}	
}

bool UnsortedList::IsFull()
{
	node* ptr;
	ptr = new node;
	if ( ptr == NULL )
	{
		return true;
	}
	
	else
	{
		delete ptr;
		return false;
	}
}

int UnsortedList::LengthIs()
{
	return length;
}

/*void UnsortedList::RetrieveItem(point& retrieve, bool& found)
{
	node* location;
	
	location = listData;
	found = false;
	
	while( (location != NULL) && !found) {
		
		if (((location->pixel).x == retrieve.x)&&((location->pixel).y == retrieve.y)) 
			{
				retrieve = location->pixel;
				found = true;
			}
		
		else
			location = location->next;
		
	}
}*/

void UnsortedList::InsertItem( nodeType* newItem )
{	
	node* location;
	
	location = new node;
	location->nodes = newItem;
	location->next = listData;
	listData = location;
	length++;
} 

/*
void UnsortedList::DeleteItem(point item)
{
	node* location = listData;
	node* tempLocation;
	if(((location->pixel).x == item.x)&&((location->pixel).y == item.y))
	{
		tempLocation = listData; // special case
		listData = listData->next;  
	}
	else {
		
		while((!( (((location->next)->pixel).x == item.x)&&(((location->next)->pixel).y == item.y) ))&& ((location->next)!=NULL))
			location = location->next;
		
		// delete node at location->next
		tempLocation=location->next;
		location->next = tempLocation->next;
	} 
	
	
	delete tempLocation;
	length--;
} 
*/
void UnsortedList::ResetList()
{
	currentPos = listData;
}

bool UnsortedList::IsLastItem()
{
	return(currentPos == NULL);
} 

/*
void UnsortedList::GetNextItem(point& item)
{
	item = currentPos->pixel;
	currentPos = currentPos->next;
}

void UnsortedList::operator=( UnsortedList& copiedList )
{
	MakeEmpty();
	copiedList.ResetList();
	point copy;
	while ( !copiedList.IsLastItem() )
	{
		copiedList.GetNextItem( copy );
		InsertItem( copy );
	}
	
}*/

