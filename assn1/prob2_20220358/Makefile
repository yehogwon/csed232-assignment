CC = g++
CXXFLAGS = -Wall -O2
STD = c++14
SRC = main.cpp
TARGET = main.out

.PHONY: all clean

all: $(TARGET)
clean: 
	rm $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(TARGET) $(SRC)
