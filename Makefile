CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb

all: compile doc

compile: main.o Interface.o Calendar.o EventMaps.o Event.o Task.o Meeting.o Trip.o Date.o
	$(CC) $(CFLAGS) main.o Interface.o Calendar.o EventMaps.o Event.o Task.o Meeting.o Trip.o Date.o -o CalendarConsoleApp

main.o:
	$(CC) $(CFLAGS) -c src/main.cpp -o main.o

Interface.o:
	$(CC) $(CFLAGS) -c src/Interface.cpp -o Interface.o

Calendar.o:
	$(CC) $(CFLAGS) -c src/Calendar.cpp -o Calendar.o

EventMaps.o:
	$(CC) $(CFLAGS) -c src/EventMaps.cpp -o EventMaps.o

Task.o:
	$(CC) $(CFLAGS) -c src/Birthday.cpp -o Task.o

Meeting.o:
	$(CC) $(CFLAGS) -c src/Meeting.cpp -o Meeting.o

Trip.o:
	$(CC) $(CFLAGS) -c src/Trip.cpp -o Trip.o

Event.o:
	$(CC) $(CFLAGS) -c src/Event.cpp -o Event.o

Date.o:
	$(CC) $(CFLAGS) -c src/Date.cpp -o Date.o

clean:
	rm -rf doc *.o doc ./CalendarConsoleApp

doc:
	doxygen Doxyfile

run:
	./CalendarConsoleApp
