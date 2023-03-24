CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD = c++14

SRC = main.cpp student.cpp list.cpp
OUT = main.out
TARGET = main.o list.o student.o main.out

.PHONY: all clean run

all: $(TARGET)

clean: 
	rm -f $(TARGET)

run: all
	./$(OUT)

main.o : main.cpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

list.o : list.cpp list.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o list.o -c list.cpp

student.o : student.cpp student.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o student.o -c student.cpp

main.out : main.o list.o student.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) main.o list.o student.o
