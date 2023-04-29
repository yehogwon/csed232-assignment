CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

SRC_PATH = src
OUT_PATH = out
SRC = $(SRC_PATH)/main.cpp $(SRC_PATH)/student.cpp $(SR_PATH)/node.cpp $(SRC_PATH)/list.cpp $(SRC_PATH)/io.cpp
HEADER = $(SRC_PATH)/student.hpp $(SRC_PATH)/node.hpp $(SRC_PATH)/list.hpp $(SRC_PATH)/io.hpp $(SRC_PATH)/exception.hpp
OUT = $(OUT_PATH)/main.out
TARGET = $(OUT_PATH)/main.o $(OUT_PATH)/student.o $(OUT_PATH)/node.o $(OUT_PATH)/list.o $(OUT_PATH)/io.o

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -rf $(OUT_PATH)

run: all
	./$(OUT)

$(OUT_PATH)/main.o : $(SRC_PATH)/main.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/main.o -c $(SRC_PATH)/main.cpp

$(OUT_PATH)/student.o : $(SRC_PATH)/student.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/student.o -c $(SRC_PATH)/student.cpp

$(OUT_PATH)/node.o: $(SRC_PATH)/node.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/node.o -c $(SRC_PATH)/node.cpp

$(OUT_PATH)/list.o : $(SRC_PATH)/list.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/list.o -c $(SRC_PATH)/list.cpp

$(OUT_PATH)/io.o : $(SRC_PATH)/io.cpp $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/io.o -c $(SRC_PATH)/io.cpp

$(OUT_PATH)/main.out : $(OUT_PATH)/main.o $(OUT_PATH)/student.o $(OUT_PATH)/node.o $(OUT_PATH)/list.o $(OUT_PATH)/io.o
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
