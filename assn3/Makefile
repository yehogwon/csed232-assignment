CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

HEADER = src/parser.hpp src/drawer.hpp src/artist.hpp
TARGET = out/main.o out/parser.o out/drawer.o out/artist.o # objective files
OUT = out/main.out # executable file

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -f $(TARGET) $(OUT)

run: all
	./$(OUT)

parser.o: src/parser.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/parser.o -c parser.cpp

drawer.o: src/drawer.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/drawer.o -c drawer.cpp

artist.o: src/artist.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/artist.o -c artist.cpp

main.o : src/main.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/main.o -c main.cpp

main.out : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
