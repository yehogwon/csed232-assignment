CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
NOWARN = -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable
STD ?= c++14

SRC_PATH = src
OUT_PATH = out

HEADER = $(SRC_PATH)/SharedPtr.h
TARGET = $(OUT_PATH)/SharedPtr_test.o # objective files
OUT = $(OUT_PATH)/assn4_p1.out # executable file

.PHONY: all clean

all: $(TARGET) $(OUT)

clean: 
	rm -rf $(OUT_PATH)

$(OUT_PATH)/SharedPtr_test.o: $(SRC_PATH)/SharedPtr_test.cc $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(NOWARN) --std=$(STD) -o $(OUT_PATH)/SharedPtr_test.o -c $(SRC_PATH)/SharedPtr_test.cc

$(OUT) : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
