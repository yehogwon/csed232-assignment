CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD = c++14

SRC = main.cpp student.cpp node.cpp list.cpp io.cpp
OUT = main.out
TARGET = main.o student.o node.o list.o io.o

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: $(TARGET) $(OUT)
	./$(OUT)

main.o : main.cpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

student.o : student.cpp student.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o student.o -c student.cpp

node.o: node.cpp node.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o node.o -c node.cpp

list.o : list.cpp list.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o list.o -c list.cpp

io.o : io.cpp io.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o io.o -c io.cpp

main.out : main.o list.o student.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
