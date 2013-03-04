CFLAGS = -gstabs -Wno-deprecated -lcurses

Driver: heap.o priority.o UnsortedList.o \
                main.cpp	
	g++ -o Driver $(CFLAGS)  heap.o priority.o UnsortedList.o\
                                        main.cpp
priority.o: priority.h priority.cpp
	g++ -c $(CFLAGS) priority.cpp

heap.o:	heap.h heap.cpp
	g++ -c $(CFLAGS) heap.cpp	

UnsortedList.o: UnsortedList.h UnsortedList.cpp
	g++ -c $(CFLAGS) UnsortedList.cpp
