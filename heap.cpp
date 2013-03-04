/*
 *  heap.cpp
 *  aStar
 *
 *  Created by Bobby's Macbook on 2/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "heap.h"

void HeapType::ReheapDown( int root, int bottom ){
	int maxChild, rightChild, leftChild;
	
	leftChild = 2*root+1;
	rightChild = 2*root+2;
	
	if(leftChild <= bottom) {  // left child is part of the heap
		if(leftChild == bottom) // only one child
			maxChild = leftChild;
		else { // two children
			if(elements[leftChild].f >= elements[rightChild].f)
				maxChild = rightChild;
			else
				maxChild = leftChild;
		}
		if(elements[root].f > elements[maxChild].f) {
			Swap(elements, root, maxChild);
			ReheapDown(maxChild, bottom);
		}
	}
}

void HeapType::ReheapUp(int root, int bottom){
	int parent;
	if(bottom > root) { // tree is not empty
		parent = (bottom-1)/2;
		if(elements[parent].f == elements[bottom].f)
		{
			if( elements[parent].g < elements[bottom].g )
			{
				Swap(elements, parent, bottom);
				ReheapUp(root, parent);
			}
		}
		else if(elements[parent].f > elements[bottom].f) {
			Swap(elements, parent, bottom);
			ReheapUp(root, parent);
		}
	}
}

void Swap( nodeType* elements, int one, int other ){
	nodeType holder;
	
	//use a holder to swap the two nodeTypes
	holder = elements[one];
	elements[one] = elements[other];
	elements[other] = holder;
} 