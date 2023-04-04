CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

SRC = main.cpp student.cpp node.cpp list.cpp io.cpp
HEADER = student.hpp node.hpp list.hpp io.hpp exception.hpp
OUT = main.out
TARGET = main.o student.o node.o list.o io.o

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: all
	./$(OUT)

main.o : main.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

student.o : student.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o student.o -c student.cpp

node.o: node.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o node.o -c node.cpp

list.o : list.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o list.o -c list.cpp

io.o : io.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o io.o -c io.cpp

main.out : main.o student.o node.o list.o io.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
