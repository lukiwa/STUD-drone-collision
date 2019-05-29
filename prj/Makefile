CXX		  := g++
CXX_FLAGS := -Wall -pedantic -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= inc
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= drone_steering.out


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
