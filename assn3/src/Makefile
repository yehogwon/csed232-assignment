CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

SRC = main.cpp # cpp files
HEADER = # header files
OUT = main.out # executable file
TARGET = main.o # objective files

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: all
	./$(OUT)

main.o : main.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

main.out : main.o student.o node.o list.o io.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
