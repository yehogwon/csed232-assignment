CC = g++
D ?=
CXXFLAGS = -Wall -O2 $(D)
NOWARN = -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable
STD ?= c++14

SRC_PATH = src
OUT_PATH = out
HEADER = $(SRC_PATH)/Image.h
TARGET = $(OUT_PATH)/image_test.o $(OUT_PATH)/Image.o # objective files
OUT = $(OUT_PATH)/assn4_p2.out # executable file

.PHONY: all clean run

all: $(TARGET) $(OUT)

clean: 
	rm -rf $(OUT_PATH)

$(OUT_PATH)/Image.o: $(SRC_PATH)/Image.cc $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	@cp ../prob1/$(SRC_PATH)/SharedPtr.h $(SRC_PATH)/
	$(CC) $(NOWARN) --std=$(STD) -o $(OUT_PATH)/Image.o -c $(SRC_PATH)/Image.cc
	@rm -f $(SRC_PATH)/SharedPtr.h

$(OUT_PATH)/image_test.o: $(SRC_PATH)/image_test.cc $(HEADER)
	@if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi
	@cp ../prob1/$(SRC_PATH)/SharedPtr.h $(SRC_PATH)/
	$(CC) $(NOWARN) --std=$(STD) -o $(OUT_PATH)/image_test.o -c $(SRC_PATH)/image_test.cc
	@rm -f $(SRC_PATH)/SharedPtr.h

$(OUT) : $(TARGET)
	$(CC) $(CXXFLAGS) --std=$(STD) -o $(OUT) $(TARGET)
