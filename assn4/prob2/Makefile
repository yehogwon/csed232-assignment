CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
STD ?= c++14

OUT_PATH = out
HEADER = src/Image.h
TARGET = $(OUT_PATH)/image_test.o $(OUT_PATH)/Image.o # objective files
OUT = $(OUT_PATH)/assn4_p2.out # executable file

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -rf $(OUT_PATH)

$(OUT_PATH)/Image.o: src/Image.cc $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/Image.o -c src/Image.cc

$(OUT_PATH)/image_test.o: src/image_test.cc $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT_PATH)/image_test.o -c src/image_test.cc

$(OUT) : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
