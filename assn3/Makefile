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

out/parser.o: src/parser.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/parser.o -c src/parser.cpp

out/drawer.o: src/drawer.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/drawer.o -c src/drawer.cpp

out/artist.o: src/artist.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/artist.o -c src/artist.cpp

out/main.o : src/main.cpp $(HEADER)
	$(CC) $(CXXFLAGS) --std=$(STD) -o out/main.o -c src/main.cpp

out/main.out : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
