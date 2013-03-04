/*
 *  priority.h
 *  
 *
 *  Created by Bobby's Macbook on 2/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "heap.h"

class PQType {
public:
    PQType(int);
    ~PQType();
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    void Enqueue(nodeType&);
    void Dequeue(nodeType&);
private:
    int numItems; // num of elements in the queue
    HeapType heap;
    int maxItems; // array size
}; 
