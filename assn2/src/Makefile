CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD = c++14

SRC = main.cpp student.cpp list.cpp
OUT = main.out
TARGET = main.o student.o list.o

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: all
	./$(OUT)

main.o : main.cpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

student.o : student.cpp student.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o student.o -c student.cpp

list.o : list.cpp list.hpp
	$(CC) $(CXXFLAGS) --std=$(STD) -o list.o -c list.cpp

main.out : main.o list.o student.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
