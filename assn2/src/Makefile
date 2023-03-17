CC = g++
CXXFLAGS = -Wall -O2
STD = c++14

SRC = main.cpp student.cpp list.cpp
TARGET = main.out

.PHONY: all clean

all: $(TARGET)
clean: 
	rm $(TARGET)

main.o : main.cpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o -c main.o main.cpp

list.o : list.cpp list.h
	$(CC) $(CXXFLAGS) --std=$(STD) -o -c list.o list.cpp

student.o : student.cpp student.h
	$(CC) $(CXXFLAGS) --std=$(STD) -o -c student.o student.cpp

main.out : main.o list.o student.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.out main.o list.o student.o
