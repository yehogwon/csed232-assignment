CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

SRC = src/main.cpp # cpp files
HEADER = # header files
TARGET = src/main.o # objective files
OUT = out/main.out # executable file

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: all
	./$(OUT)

main.o : main.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o main.o -c main.cpp

main.out : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
