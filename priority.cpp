/*
 *  priority.cpp
 *  
 *
 *  Created by Bobby's Macbook on 2/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "priority.h"

void PQType::Dequeue(nodeType& item)
{
	item = heap.elements[0];
	heap.elements[0] = heap.elements[numItems-1];
	numItems--;
	heap.ReheapDown(0, numItems-1);
}

void PQType::Enqueue(nodeType& newItem)
{
	numItems++;
	heap.elements[numItems-1] = newItem;
	heap.ReheapUp(0, numItems-1);
}


PQType::PQType(int max)
{
	maxItems = max;
	heap.elements = new nodeType[max];
	numItems = 0;
}


void PQType::MakeEmpty()
{
	numItems = 0;
}


PQType::~PQType()
{
	delete [ ] heap.elements;
} 

bool PQType::IsFull() const
{
	return numItems == maxItems;
}


bool PQType::IsEmpty() const
{
	return numItems == 0;
} 

