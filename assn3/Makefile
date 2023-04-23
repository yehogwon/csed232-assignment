CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

OUT_PATH = out
HEADER = src/parser.hpp src/drawer.hpp src/artist.hpp
TARGET = $(OUT_PATH)/main.o $(OUT_PATH)/parser.o $(OUT_PATH)/drawer.o $(OUT_PATH)/artist.o # objective files
OUT = $(OUT_PATH)/assn3.out # executable file

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -rf $(OUT_PATH)

$(OUT_PATH)/parser.o: src/parser.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/parser.o -c src/parser.cpp

$(OUT_PATH)/drawer.o: src/drawer.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/drawer.o -c src/drawer.cpp

$(OUT_PATH)/artist.o: src/artist.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/artist.o -c src/artist.cpp

$(OUT_PATH)/main.o : src/main.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/main.o -c src/main.cpp

$(OUT) : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
