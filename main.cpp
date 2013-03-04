/*
 *  main.cpp
 *  
 *
 *  Created by Bobby's Macbook on 2/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include "UnsortedList.h"
#include <curses.h>
#include <stack>
#include "formatted_console_io_v14.h"

using namespace std;

void buildPlane( bool [][49], nodeType&, nodeType& );

void buildPlaneNoDisplay(bool [][49], nodeType&, nodeType& );

void printPath ( nodeType*, nodeType&, nodeType& );

double compH( nodeType&, nodeType& );

double compHaStar( nodeType&, nodeType& );

double aStar( bool [][49], nodeType&, nodeType&, nodeType*& , UnsortedList&  );

double thetaStar( bool [][49], nodeType& , nodeType&, nodeType*& , UnsortedList&  );

double visibility( bool [][49], nodeType& , nodeType&, nodeType*&, UnsortedList& );

bool lineOfSight(bool [][49], nodeType&,nodeType&);

int main()
{
	startCurses();
	clock_t beginT, endT;
	nodeType start;
	double averageDiff;
	double percentDiff;
	double diff;
	double sum1, sum2;
	nodeType end;
	nodeType* memory;
	UnsortedList deletion;
	double pathCost;
	double pathCost2;
	int choice;
	bool running = true;
	srand( time(NULL));
	bool blocked[99][49];
	
	nodeType one;
	nodeType other;
	one.x = 3;
	one.y = 3;
	other.x = 4;
	other.y = 4;
	bool test;
	
	while (running )
	{
		setColor( COLOR_YELLOW, COLOR_BLUE, SET_BRIGHT );
		clearScreen(0,0,210,63);
		setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
		clearScreen(30,8,180,50);
		setColor( COLOR_BLACK, COLOR_WHITE, SET_BRIGHT );
		clearScreen(60,15,150,43);
		printStringAt( 105, 16, "WELCOME TO BOBBY AND JERRY'S PATH PLANNING PROGRAM", "CENTER" );
		printStringAt( 105, 40, "PLEASE PRESS THE KEY THAT CORRESPONDS TO YOUR CHOICE", "CENTER" );
		printStringAt( 105, 19, "PRESS 1 TO RUN THE A* ALGORITHM ON A RANDOM GRID", "CENTER" );
		printStringAt( 105, 22, "PRESS 2 TO RUN THE THETA* ALGORITHM ON A RANDOM GRID", "CENTER" );
		printStringAt( 105, 25, "PRESS 3 TO RUN THE A* ALGORITHM WITH VISIBILITY GRAPHS", "CENTER" );
		printStringAt( 105, 28, "PRESS 4 TO RUN THETA* THEN A* WITH VISIBILITY GRAPHS ON THE SAME GRID", "CENTER" );
		printStringAt( 105, 31, "PRESS 5 TO TEST THETA* AGAINST VISIBILITY GRAPHS  ", "CENTER" );
		printStringAt( 105, 34, "PRESS 6 TO TEST A* AGAINST THETA*  ", "CENTER" );
		printStringAt( 105, 37, "PRESS 7 TO EXIT THE PROGRAM", "CENTER" );
		printCharAt( 148, 40, ' ' );
		
		choice = waitForInput( FIXED_WAIT );
		
		if( choice == '1' )
		{
			setColor( COLOR_YELLOW, COLOR_CYAN, SET_BRIGHT );
			clearScreen(0,0,210,63);
			buildPlane( blocked, start, end );
			start.g = 0;
			start.h = compH( start, end );
			start.f = start.h;
			start.parent = NULL;
			end.g = 100000;
			end.h = 0;
			end.f = end.g;
			pathCost = aStar(  blocked, start, end, memory, deletion );
			printPath( memory, start, end );
			deletion.MakeEmpty();
		}
		
		else if( choice == '2' )
		{
			setColor( COLOR_YELLOW, COLOR_CYAN, SET_BRIGHT );
			clearScreen(0,0,210,63);
			buildPlane( blocked, start, end );
			start.g = 0;
			start.h = compH( start, end );
			start.f = start.h;
			start.parent = NULL;
			end.g = 100000;
			end.h = 0;
			end.f = end.g;
			pathCost = thetaStar(  blocked, start, end, memory, deletion );
			printPath( memory, start, end );
			deletion.MakeEmpty();
		}
		
		
		else if( choice == '3' )
		{
			setColor( COLOR_YELLOW, COLOR_CYAN, SET_BRIGHT );
			clearScreen(0,0,210,63);
			buildPlane( blocked, start, end );
			start.g = 0;
			start.h = compH( start, end );
			start.f = start.h;
			start.parent = NULL;
			end.g = 100000;
			end.h = 0;
			end.f = end.g;
			pathCost = visibility( blocked, start, end, memory, deletion );
			printPath( memory, start, end );
			deletion.MakeEmpty();

			
		}
		
		else if( choice == '4' )
		{
			setColor( COLOR_YELLOW, COLOR_CYAN, SET_BRIGHT );
			clearScreen(0,0,210,63);
			buildPlane( blocked, start, end );
			start.g = 0;
			start.h = compH( start, end );
			start.f = start.h;
			start.parent = NULL;
			end.g = 100000;
			end.h = 0;
			end.f = end.g;
			pathCost = thetaStar(  blocked, start, end, memory, deletion );
			printPath( memory, start, end );
			deletion.MakeEmpty();
			
			//Clear the grid for visibility graph
			setColor( COLOR_BLUE, COLOR_CYAN, SET_BRIGHT );
			for ( int i = 0; i < 100; i++ )
			{
				for( int j = 0; j < 50; j++ )
				{
					
					printCharAt( 2*i+5 , j+5 ,'.');
					
					
				}	
			}

			setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*start.x+5 , start.y+5 ,'S');
			printCharAt( 2*end.x+5 , end.y+5 ,'G');
			
			
			
			pathCost = visibility( blocked, start, end, memory, deletion );
			printPath( memory, start, end );
			deletion.MakeEmpty();
			
		}
		
		else if( choice == '5' )
		{
			averageDiff = 0;
			percentDiff = 0;
			sum1 = 0;
			sum2 = 0;
			setColor(COLOR_BLACK, COLOR_CYAN, SET_BRIGHT);
			clearScreen(0,0,210,63);
			printStringAt( 15, 6, "THETA*", "LEFT" );
			printStringAt( 25, 6, "VISIBILITY", "LEFT" );
			printStringAt( 40, 6, "DIFF.", "LEFT" );

			for (int index = 0; index < 50; index ++ )
			{
				buildPlaneNoDisplay( blocked, start, end );
				pathCost = thetaStar(  blocked, start, end, memory, deletion );
				deletion.MakeEmpty();
				pathCost2 = visibility( blocked, start, end, memory, deletion );
				deletion.MakeEmpty();
				diff = pathCost - pathCost2;
				printDoubleAt( 15, 8+index, pathCost, 2, "LEFT" );
				printDoubleAt( 25, 8+index, pathCost2, 2, "LEFT" );
				printDoubleAt( 40, 8+index, abs(diff), 2, "LEFT" );
				sum1 += pathCost;
				sum2 += pathCost2;
				averageDiff += diff;
				percentDiff += (diff/pathCost);
			}

			percentDiff /= 50;
			percentDiff *= 100;
			
			printStringAt( 3, 60, "TOTAL:", "LEFT" );
			printDoubleAt( 15, 60, sum1,2, "LEFT" );
			printDoubleAt( 25, 60, sum2,2, "LEFT" );
			printDoubleAt( 40, 60, averageDiff,2, "LEFT" );
			printStringAt( 50, 32, "ON AVERAGE, VISIBILITY GRAPHS ARE ", "LEFT" );
			printDoubleAt( 84, 32, percentDiff, 2, "LEFT" );
			printStringAt( 89, 32, "PERCENT MORE OPTIMAL THAN THETA*.", "LEFT" );
			
			waitForInput( FIXED_WAIT );
			
		}
		
		else if( choice == '6' )
		{
			averageDiff = 0;
			percentDiff = 0;
			sum1 = 0;
			sum2 = 0;
			setColor(COLOR_BLACK, COLOR_CYAN, SET_BRIGHT);
			clearScreen(0,0,210,63);
			printStringAt( 15, 6, "A*", "LEFT" );
			printStringAt( 25, 6, "THETA*", "LEFT" );
			printStringAt( 40, 6, "DIFF.", "LEFT" );
			
			for (int index = 0; index < 50; index ++ )
			{
				buildPlaneNoDisplay( blocked, start, end );
				pathCost = aStar(  blocked, start, end, memory, deletion );
				deletion.MakeEmpty();
				pathCost2 = thetaStar( blocked, start, end, memory, deletion );
				deletion.MakeEmpty();
				diff = pathCost - pathCost2;
				printDoubleAt( 15, 8+index, pathCost, 2, "LEFT" );
				printDoubleAt( 25, 8+index, pathCost2, 2, "LEFT" );
				printDoubleAt( 40, 8+index, abs(diff), 2, "LEFT" );
				sum1 += pathCost;
				sum2 += pathCost2;
				averageDiff += diff;
				percentDiff += (diff/pathCost);
			}
			
			percentDiff /= 50;
			percentDiff *= 100;
			
			printStringAt( 3, 60, "TOTAL:", "LEFT" );
			printDoubleAt( 15, 60, sum1,2, "LEFT" );
			printDoubleAt( 25, 60, sum2,2, "LEFT" );
			printDoubleAt( 40, 60, averageDiff,2, "LEFT" );
			printStringAt( 50, 32, "ON AVERAGE, THETA* IS ", "LEFT" );
			printDoubleAt( 72, 32, percentDiff, 2, "LEFT" );
			printStringAt( 77, 32, "PERCENT MORE OPTIMAL THAN A*.", "LEFT" );
			
			waitForInput( FIXED_WAIT );
			
		}
		else if( choice == '7' )
		{
			running = false;
			
		}
		
		else if( choice == ';' )
		{
			sum1 = 0;
			sum2 = 0;
			averageDiff = 0;
			
			for (int index = 0; index < 100; index ++ )
			{
				buildPlaneNoDisplay( blocked, start, end );
				
				beginT = clock();
				pathCost = thetaStar(  blocked, start, end, memory, deletion );
				endT = clock();
				sum1 += (endT - beginT);
				deletion.MakeEmpty();
				
				beginT = clock();
				pathCost = aStar(  blocked, start, end, memory, deletion );
				endT = clock();
				sum2 += (endT - beginT);
				deletion.MakeEmpty();
			}
			
			sum1 /= 1000;
			sum2 /= 1000;
			
			averageDiff =  sum1 - sum2;
			averageDiff /= 100;
			
			setColor(COLOR_BLACK, COLOR_CYAN, SET_BRIGHT);
			clearScreen(0,0,210,63);
			printStringAt( 15, 6, "EACH ALGORITHM WILL BE RUN 100 TIMES AND TIMED", "LEFT" );
		    printStringAt( 15, 8, "FOR 100 RANDOM ITERATIONS, THETA* TOOK         MILLISECONDS.", "LEFT" );
			printStringAt( 15, 10, "FOR 100 RANDOM ITERATIONS, A* TOOK          MILLISECONDS.", "LEFT" );
			printStringAt( 15, 12, "ON AVERAGE, A* IS         MILLISECONDS FASTER THAN THETA*.", "LEFT" );
			printDoubleAt( 55, 8, sum1, 2, "LEFT" );
			printDoubleAt( 51, 10, sum2, 2, "LEFT" );
			printDoubleAt( 33, 12, averageDiff, 3, "LEFT" );
			
			waitForInput( FIXED_WAIT );
		}
		
		
	}	
	
	endCurses();
	
}


void buildPlane( bool blocked[][49], nodeType& start, nodeType& end )
{
	int random;
	int x;
	int y;
	
	//randomize and print the blocked squares
	for ( int i = 0; i < 99; i++ )
	{
		for( int j = 0; j < 49; j++ )
		{
			random = rand()%10;
		//	setColor( COLOR_YELLOW, COLOR_RED, SET_BRIGHT );
			setColor( COLOR_RED, COLOR_CYAN, SET_BRIGHT );
			if (random==0)
			{
				blocked[i][j] = true;
				printCharAt( 2*i+6 , j+6, '#' );
			}
			else
				blocked[i][j] = false;
		}	
	}
	
	//print all the points
	setColor( COLOR_BLUE, COLOR_CYAN, SET_BRIGHT );
	for ( int i = 0; i < 100; i++ )
	{
		for( int j = 0; j < 50; j++ )
		{
			
			printCharAt( 2*i+5 , j+5 ,'.');
			
			
		}	
	}
	//find the start and finish and print them
	x = rand()%100;
	y = rand()%50;
	
	
	start.x = x;
	start.y = y;
	
	setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );
	printCharAt( 2*x+5 , y+5 ,'S');
	
	x = rand()%100;
	y = rand()%50;
	
	end.x = x;
	end.y = y;

	printCharAt( 2*x+5 , y+5 ,'G');
	
	}


void buildPlaneNoDisplay( bool blocked[][49], nodeType& start, nodeType& end )
{
	int random;
	int x;
	int y;
	
	//randomize and print the blocked squares
	for ( int i = 0; i < 99; i++ )
	{
		for( int j = 0; j < 49; j++ )
		{
			random = rand()%10;
			if (random==0)
			{
				blocked[i][j] = true;
			}
			else
				blocked[i][j] = false;
		}	
	}
	
	//find the start and finish and print them
	x = rand()%100;
	y = rand()%50;
	
	
	start.x = x;
	start.y = y;
	

	x = rand()%100;
	y = rand()%50;
	
	end.x = x;
	end.y = y;
	
	
}





double compH( nodeType& one, nodeType& other )
{
	double h;
	h = pow( double(one.x- other.x), 2 ) + pow( double(one.y- other.y), 2 );
	h = pow( h, 0.5 );
	return h;
}

double compHaStar( nodeType& one, nodeType& other )
{
	double h;
	h = pow( 2, 0.5 ) * min( abs(one.x - other.x), abs(one.y - other.y) );
	h += max( abs(one.x - other.x), abs(one.y - other.y) );
	h -=  min( abs(one.x - other.x), abs(one.y - other.y) );
	return h;
}


double aStar( bool blocked[][49], nodeType& start, nodeType& end, nodeType*& memory, UnsortedList& deletion )
{
	PQType priority(10000);
	
	stack<nodeType> pathforward;
	stack<nodeType> pathback;
	double path;
	int choice;
	nodeType current;
	nodeType testing;
	bool running = true;
	int maximums[100][50];
	bool found = false;
	priority.Enqueue( start );
	
	for( int i=0; i<100; i++ ){
		for( int j=0; j<50; j++ )
		{
			maximums[i][j]=90000;
			
		}
	}
	while (!found)
	{
		if ( priority.IsEmpty() )
		{
			//printStringAt( 10, 56, "NO PATH TO GOAL FOUND.", "LEFT" );
			//printStringAt( 45, 56, "Press any key to continue...", "LEFT");	
			found = false;
			return 0;
		}
		priority.Dequeue( current );
		memory = new nodeType;
		*memory = current;
		deletion.InsertItem(memory);
		if( (current.x == end.x) && (current.y==end.y) )
		{
			found = true;
			break;
		}
			
		//test all cases along left side
		if ( current.x > 0 )
		{
			if ( current.y > 0 )
			{
				if (blocked[current.x-1][current.y-1] == false)
					{
						testing.x = current.x-1;
						testing.y = current.y-1;
						testing.g = current.g + pow(2,.5);
						testing.h = compHaStar( testing, end);
						testing.f = testing.g + testing.h;
						testing.parent = memory;
						if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}
					}
				
			}
			
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x-1][current.y] == false))
			{
				testing.x = current.x-1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compHaStar( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}


			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x-1][current.y] == false)
				{
					testing.x = current.x-1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compHaStar( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}
				}
			}
		}
		
		if ( current.y > 0 )
		{
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x][current.y-1] == false))
			{
				testing.x = current.x;
				testing.y = current.y-1;
				testing.g = current.g + 1;
				testing.h = compHaStar( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}
			}
			
			
			
			if ( current.x < 99 )
			{
				if (blocked[current.x][current.y-1] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y-1;
					testing.g = current.g + pow(2,.5);
					testing.h = compHaStar( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}

				}
			}
		}
		
		if ( current.x < 99 )
		{
			if ((blocked[current.x][current.y-1] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x+1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compHaStar( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}

			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x][current.y] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compHaStar( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;

					if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}

				}
			}
		}
		
		if ( current.y < 49 )
		{
			if ((blocked[current.x-1][current.y] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x;
				testing.y = current.y+1;
				testing.g = current.g + 1;
				testing.h = compHaStar( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;

				if (maximums[testing.x][testing.y] > testing.f)
						{
							priority.Enqueue( testing );
							maximums[testing.x][testing.y] = testing.f;
						}

			}
		}
		
		
			
	}
	
	path = (*memory).g;
	return path;
	
	
}


double thetaStar( bool blocked[][49], nodeType& start, nodeType& end, nodeType*& memory, UnsortedList& deletion )
{
	PQType priority(20000);
	
	stack<nodeType> pathforward;
	stack<nodeType> pathback;
	int choice;
	double path;
	nodeType current;
	nodeType testing;
	bool running = true;
	int maximums[100][50];
	bool found = false;
	priority.Enqueue( start );
	
	for( int i=0; i<100; i++ ){
		for( int j=0; j<50; j++ )
		{
			maximums[i][j]=90000;
			
		}
	}
	
	//run once without path two for start
	for(int i=0; i < 1; i++)
	{
		
	
		if ( priority.IsEmpty() )
		{
			printStringAt( 10, 56, "NO PATH TO GOAL FOUND.", "LEFT" );
			printStringAt( 45, 56, "Press any key to continue...", "LEFT");	
			found = false;
			break;
		
		}
		priority.Dequeue( current );
		memory = new nodeType;
		*memory = current;
		deletion.InsertItem(memory);
		if( (current.x == end.x) && (current.y==end.y) )
		{
			found = true;
			break;
		}
		
		//test all cases along left side
		if ( current.x > 0 )
		{
			if ( current.y > 0 )
			{
				if (blocked[current.x-1][current.y-1] == false)
				{
					testing.x = current.x-1;
					testing.y = current.y-1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
				}
				
			}
			
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x-1][current.y] == false))
			{
				testing.x = current.x-1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
				
			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x-1][current.y] == false)
				{
					testing.x = current.x-1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
									
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
				}
			}
		}
		
		if ( current.y > 0 )
		{
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x][current.y-1] == false))
			{
				testing.x = current.x;
				testing.y = current.y-1;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
			}
			
			
			
			if ( current.x < 99 )
			{
				if (blocked[current.x][current.y-1] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y-1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
					
				}
			}
		}
		
		if ( current.x < 99 )
		{
			if ((blocked[current.x][current.y-1] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x+1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x][current.y] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
					
				}
			}
		}
		
		if ( current.y < 49 )
		{
			if ((blocked[current.x-1][current.y] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x;
				testing.y = current.y+1;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
			}
		}
		
		
		
	}
	
	
	
	
	
	
	while (!found)
	{
		if ( priority.IsEmpty() )
		{
			//printStringAt( 10, 56, "NO PATH TO GOAL FOUND.", "LEFT" );
			//printStringAt( 45, 56, "Press any key to continue...", "LEFT");	
			found = false;
			return 0;
		}
		priority.Dequeue( current );
		memory = new nodeType;
		*memory = current;
		deletion.InsertItem(memory);
		if( (current.x == end.x) && (current.y==end.y) )
		{
			found = true;
			break;
		}
		
		//test all cases along left side
		if ( current.x > 0 )
		{
			if ( current.y > 0 )
			{
				if (blocked[current.x-1][current.y-1] == false)
				{
					testing.x = current.x-1;
					testing.y = current.y-1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if( lineOfSight( blocked, *((*memory).parent), testing ) )
				{
					//PATH TWO
					if( ((*((*memory).parent)).g + compH( *((*memory).parent), testing )) <= testing.g )
					{
						testing.g = ((*((*memory).parent)).g + compH( *((*memory).parent), testing ));
						testing.parent = (*memory).parent;
						testing.f = testing.g+testing.h;
					}
				}
					
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
				}
				
			}
			
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x-1][current.y] == false))
			{
				testing.x = current.x-1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if( lineOfSight( blocked, *(current.parent), testing ) )
				{
					//PATH TWO
					if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
					{
						testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
						testing.parent = current.parent;
						testing.f = testing.g+testing.h;
					}
				}
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
				
			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x-1][current.y] == false)
				{
					testing.x = current.x-1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if( lineOfSight( blocked, *(current.parent), testing ) )
					{
						//PATH TWO
						if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
						{
							testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
							testing.parent = current.parent;
							testing.f = testing.g+testing.h;
						}
					}
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
				}
			}
		}
		
		if ( current.y > 0 )
		{
			if ((blocked[current.x-1][current.y-1] == false) || (blocked[current.x][current.y-1] == false))
			{
				testing.x = current.x;
				testing.y = current.y-1;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if( lineOfSight( blocked, *(current.parent), testing ) )
				{
					//PATH TWO
					if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
					{
						testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
						testing.parent = current.parent;
						testing.f = testing.g+testing.h;
					}
				}
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
			}
			
			
			
			if ( current.x < 99 )
			{
				if (blocked[current.x][current.y-1] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y-1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if( lineOfSight( blocked, *(current.parent), testing ) )
					{
						//PATH TWO
						if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
						{
							testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
							testing.parent = current.parent;
							testing.f = testing.g+testing.h;
						}
					}
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
					
				}
			}
		}
		
		if ( current.x < 99 )
		{
			if ((blocked[current.x][current.y-1] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x+1;
				testing.y = current.y;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if( lineOfSight( blocked, *(current.parent), testing ) )
				{
					//PATH TWO
					if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
					{
						testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
						testing.parent = current.parent;
						testing.f = testing.g+testing.h;
					}
				}
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
			}
			
			if ( current.y < 49 )
			{
				if (blocked[current.x][current.y] == false)
				{
					testing.x = current.x+1;
					testing.y = current.y+1;
					testing.g = current.g + pow(2,.5);
					testing.h = compH( testing, end);
					testing.f = testing.g + testing.h;
					testing.parent = memory;
					if( lineOfSight( blocked, *(current.parent), testing ) )
					{
						//PATH TWO
						if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
						{
							testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
							testing.parent = current.parent;
							testing.f = testing.g+testing.h;
						}
					}
					
					if (maximums[testing.x][testing.y] > testing.f)
					{
						priority.Enqueue( testing );
						maximums[testing.x][testing.y] = testing.f;
					}
					
				}
			}
		}
		
		if ( current.y < 49 )
		{
			if ((blocked[current.x-1][current.y] == false) || (blocked[current.x][current.y] == false))
			{
				testing.x = current.x;
				testing.y = current.y+1;
				testing.g = current.g + 1;
				testing.h = compH( testing, end);
				testing.f = testing.g + testing.h;
				testing.parent = memory;
				if( lineOfSight( blocked, *(current.parent), testing ) )
				{
					//PATH TWO
					if( ((*(current.parent)).g + compH( *(current.parent), testing )) <= testing.g )
					{
						testing.g = ((*(current.parent)).g + compH( *(current.parent), testing ));
						testing.parent = current.parent;
						testing.f = testing.g+testing.h;
					}
				}
				if (maximums[testing.x][testing.y] > testing.f)
				{
					priority.Enqueue( testing );
					maximums[testing.x][testing.y] = testing.f;
				}
				
			}
		}
		
		
		
	}
	path = (*memory).g;
	return path;
	
	
}




////////////////////////////////////////////////////////////////////////
bool lineOfSight( bool blocked[][49], nodeType& currentNode,nodeType& nextNode)
{
	int x_0 = currentNode.x;
	int y_0 = currentNode.y;
	int x_1 = nextNode.x;
	int y_1 = nextNode.y;
	int sy, sx;
	
	double f = 0;
	
	int dy = y_1 - y_0;
	int dx = x_1 - x_0;
	
	if( dy < 0 )
	{
		dy *= -1;
		sy = -1;
	}
	else {
		sy = 1;
	}
	
	if( dx < 0 )
	{
		dx *= -1;
		sx = -1;
	}
	else {
		sx = 1;
	}
	
	if( dx >= dy )
	{
		while( x_0 != x_1 )
		{
			f += dy;
			if( f >= dx )
			{
				if( blocked[x_0+((sx-1)/2)][y_0+((sy-1)/2)] )
				{
					return false;
				}
				y_0 += sy;
				f -= dx;
			}
			if ( (f != 0) && ( blocked[x_0+((sx-1)/2)][y_0+((sy-1)/2)] ))
			{
				return false;
			}
			if ( (dy == 0) && ( blocked[x_0+((sx-1)/2)][y_0] ) && ( blocked[x_0+((sx-1)/2)][y_0-1] ))
			{
				return false;
			}
			x_0 += sx;
		}
	}
	
	else 
	{
		while( y_0 != y_1 )
		{
			f += dx;
			if( f >= dy )
			{
				if( blocked[x_0+((sx-1)/2)][y_0+((sy-1)/2)] )
				{
					return false;
				}
				x_0 += sx;
				f -= dy;
			}
			if ( (f != 0) && ( blocked[x_0+((sx-1)/2)][y_0+((sy-1)/2)] ))
			{
				return false;
			}
			if ( (dx == 0) && ( blocked[x_0][y_0+((sy-1)/2)] ) && ( blocked[x_0-1][y_0+((sy-1)/2)] ))
			{
				return false;
			}
			y_0 += sy;
		}
	}

	return true;
}


double visibility( bool blocked[][49], nodeType& start, nodeType& end, nodeType*& memory, UnsortedList& deletion )
{
	PQType priority(10000);
	
	stack<nodeType> pathforward;
	stack<nodeType> pathback;
	int choice;
	double path;
	nodeType current;
	nodeType testing;
	bool running = true;
	int maximums[100][50];
	bool found = false;
	priority.Enqueue( start );
	
	for( int i=0; i<100; i++ ){
		for( int j=0; j<50; j++ )
		{
			maximums[i][j]=90000;
			
		}
	}
	while (!found)
	{
		if ( priority.IsEmpty() )
		{
		//	printStringAt( 10, 56, "NO PATH TO GOAL FOUND.", "LEFT" );
		//	printStringAt( 45, 56, "Press any key to continue...", "LEFT");	
			found = false;
			return 0;
		}
		priority.Dequeue( current );
		memory = new nodeType;
		*memory = current;
		deletion.InsertItem(memory);
		if( (current.x == end.x) && (current.y==end.y) )
		{
			found = true;
			break;
		}
		
		//Test goal node first
		testing.x = end.x;
		testing.y = end.y;
		if ( lineOfSight( blocked, current, testing ) )
		{
			testing.g = current.g + compH( testing, current);
			testing.h = compH( testing, end);
			testing.f = testing.g + testing.h;
			testing.parent = memory;
			if (maximums[testing.x][testing.y] > testing.f)
			{
				priority.Enqueue( testing );
				maximums[testing.x][testing.y] = testing.f;
			}
		}
		
		//test all corner points and enqueue valid ones
	else
	{
		for( int index = 0; index < 99; index++ )
		{
			for ( int index2 = 0; index2 < 49; index2++ )
			{
				if ( blocked[index][index2] )
				{
				
					testing.x = index;
					testing.y = index2;
					if ( lineOfSight( blocked, current, testing ) )
						{
							testing.g = current.g + compH( testing, current);
							testing.h = compH( testing, end);
							testing.f = testing.g + testing.h;
							testing.parent = memory;

							if (maximums[testing.x][testing.y] > testing.f)
							{
								priority.Enqueue( testing );
								maximums[testing.x][testing.y] = testing.f;
							}
							
						}
						
					testing.x = index;
					testing.y = index2+1;
					if ( lineOfSight( blocked, current, testing ))
						{
							testing.g = current.g + compH( testing, current);
							testing.h = compH( testing, end);
							testing.f = testing.g + testing.h;
							testing.parent = memory;
							if (maximums[testing.x][testing.y] > testing.f)
							{
								priority.Enqueue( testing );
								maximums[testing.x][testing.y] = testing.f;
							}
								
						}
						
					testing.x = index+1;
					testing.y = index2;
					if ( lineOfSight( blocked, current, testing ))
						{
							testing.g = current.g + compH( testing, current);
							testing.h = compH( testing, end);
							testing.f = testing.g + testing.h;
							testing.parent = memory;
							if (maximums[testing.x][testing.y] > testing.f)
							{
								priority.Enqueue( testing );
								maximums[testing.x][testing.y] = testing.f;
							}
								
						}
							
					testing.x = index+1;
					testing.y = index2+1;
					if ( lineOfSight( blocked, current, testing ))
						{
							testing.g = current.g + compH( testing, current);
							testing.h = compH( testing, end);
							testing.f = testing.g + testing.h;
							testing.parent = memory;
							if (maximums[testing.x][testing.y] > testing.f)
							{
								priority.Enqueue( testing );
								maximums[testing.x][testing.y] = testing.f;
							}
								
						}
					
				}
			}
		}
	}
		
	}
	path = (*memory).g;
	return path;
}


void printPath ( nodeType* memory, nodeType& start, nodeType& end )
{
	
	stack<nodeType> pathforward;
	stack<nodeType> pathback;
	nodeType testing;
	bool running = true;
	int choice;
	
	setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
	printStringAt( 10, 56, "The path length is: ", "LEFT");
	printStringAt( 45, 56, "Press right to traverse forward, left to traverse backwards, and q to quit.", "LEFT");	
	printDoubleAt( 30, 56,(*memory).g, 2, "LEFT" ); 

	
	setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );	
	pathforward.push( *memory );
	memory = (*memory).parent;
	while ( (*memory).parent != NULL )
	{
		pathforward.push( *memory );
		printCharAt( 2*(*memory).x +5 , (*memory).y + 5, '.' );
		memory = (*memory).parent;
	}
	pathforward.push( *memory );
	
	testing = (*memory);
	
	while (running == true)
	{
		if( ((testing).x == start.x) && ((testing).y == start.y))
		{
			setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, 'S' );
		}
		
		else if( ((testing).x == end.x) && ((testing).y == end.y))
		{
			setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, 'G' );
		}
		
		else
		{
			setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, '.' );
		}
		
		printStringAt( 10, 58, "X: ", "LEFT");
		printIntAt( 13, 58, testing.x, "LEFT" );
		printStringAt( 17, 58, "| Y: ", "LEFT");
		printIntAt( 22, 58, testing.y, "LEFT" );
		printStringAt( 26, 58, "| f(x): ", "LEFT");
		printDoubleAt( 34, 58, testing.f, 2, "LEFT" );
		printStringAt( 40, 58, "| g(x): ", "LEFT");
		printDoubleAt( 48, 58, testing.g, 2, "LEFT" );
		printStringAt( 54, 58, "| h(x): ", "LEFT");
		printDoubleAt( 62, 58, testing.h, 2, "LEFT" );
		
		
		choice = waitForInput( FIXED_WAIT );
		
		clearScreen( 10, 58, 70, 58);
		if( ((testing).x == start.x) && ((testing).y == start.y))
		{
			setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, 'S' );
		}
		
		else if( ((testing).x == end.x) && ((testing).y == end.y))
		{
			setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, 'G' );
		}
		
		else
		{
			setColor( COLOR_WHITE, COLOR_CYAN, SET_BRIGHT );
			printCharAt( 2*(testing).x +5 , (testing).y + 5, '.' );
		}
		
		if( choice == KB_LEFT_ARROW )
		{
			if( !pathback.empty() )
			{
				pathforward.push( testing );
				testing = pathback.top();
				pathback.pop();
			}
		}
		
		else if( choice == KB_RIGHT_ARROW )
		{
			if( !pathforward.empty() )
			{
				pathback.push( testing );
				testing = pathforward.top();
				pathforward.pop();
			}
		}
		
		else if ( (choice == 'q') || (choice == 'Q') )
		{
			running = false;
		}
	}
	setColor( COLOR_BLACK, COLOR_CYAN, SET_BRIGHT );
	clearScreen( 10, 56, 160, 58);
	printStringAt( 10, 58, "Press any key to continue... ", "LEFT");
	
}



