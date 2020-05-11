## Variables
CXX = g++
BIN_NAME = NonGravitar
BIN := $(BIN_NAME).exe

## Paths
BUILD_DIR = build
SRC_DIR = src
# edit to point to SFML install dir
SFML_DIR = E:/Desktop/SFML-2.5.1
SFML_INC = -I $(SFML_DIR)/include
SFML_LIB = -L $(SFML_DIR)/lib

## Files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRC:.cpp=.o)

## Options
CXXFLAGS += -Wall -Wextra -g -ggdb
# add to the next line all dependencies we need, "-s" means static version
LIBS = -lsfml-graphics -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

## Commands
.PHONY: all info clean

all: | $(BUILD_DIR) $(BIN)

$(BUILD_DIR):
	@echo "Build directory not found, creating a new one"
	mkdir $@

$(BIN): $(OBJS)
	$(CXX) -o $(SRC_DIR)/$(BIN) $(subst $(SRC_DIR),$(BUILD_DIR),$^) $(CXXFLAGS) $(SFML_INC) -I . $(SFML_LIB) $(LIBS)

%.o: %.cpp
	$(CXX) -MMD -c -o $(subst $(SRC_DIR),$(BUILD_DIR),$@) $^ $(SFML_INC)

info:
	@echo " Info..."
	@echo " SOURCES = $(SRC)"
	@echo " OBJECTS = $(OBJS)"

clean:
	del $(BUILD_DIR)
