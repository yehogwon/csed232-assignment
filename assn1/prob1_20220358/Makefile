CC = g++
CXXFLAGS = -Wall -O2
SRC = main.cpp
TARGET = main.out

.PHONY: all clean

all: $(TARGET)
clean: 
	rm $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CXXFLAGS) --std=c++11 -o $(TARGET) $(SRC)
