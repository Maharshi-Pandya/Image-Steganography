CC = g++
CXXFLAGS += -Wall -Wextra -pedantic-errors

# required for sfml
LDLIBS := $(shell pkg-config sfml-all --libs)

BIN_DIR = ./bin
SOURCES = test.cpp

# list 
LIST := $(BIN_DIR)/ImStegTest

all: $(LIST)

# what to do
$(BIN_DIR)/%: $(SOURCES)
	$(CC) $(CXXFLAGS) $< $(LDLIBS) -o $@

clean:
	$(RM) $(BIN_DIR)/*