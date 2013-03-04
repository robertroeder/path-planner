/*
 *  heap.h
 *  aStar
 *
 *  Created by Bobby's Macbook on 2/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

struct nodeType{
	int x;
	int y;
	double f;
	double g;
	double h;
	nodeType* parent;
};

struct HeapType {
	void ReheapDown(int, int);
	void ReheapUp(int, int);
	nodeType *elements; // dynamic array
	int numElements; 
}; 

void Swap( nodeType*, int, int );