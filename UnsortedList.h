/*
 *  UnsortedList.h
 */

#include <iostream>
#include "priority.h"

struct node {
	nodeType* nodes;
	node* next;
};

class UnsortedList {
public:
    UnsortedList();
//    ~UnsortedList();
    void MakeEmpty();
    bool IsFull();
    int LengthIs();
//    void RetrieveItem(nodeType*&, bool&);
    void InsertItem(nodeType*);
//    void DeleteItem(nodeType*);
    void ResetList();
    bool IsLastItem();
//    void GetNextItem(nodeType*&);
//	void operator=( UnsortedList&);
	
private:
    int length;
    node* listData;
    node* currentPos;
	
};