CXX = g++
BIN_NAME = nongravitar
ODIR  = .\obj
CXXFLAGS += -Wall -Wextra -g -ggdb


BIN := $(BIN_NAME).exe

SRC := $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
# edit to point to SFML install dir
SFML_DIR = C:\Users\Paolo\ Marzolo\Downloads\SFML-2.5.1
# add to the next line all dependencies we need, "-s" means static version
LIBS = -lsfml-graphics -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system 

SFML_INC = -I $(SFML_DIR)\include
SFML_LIB = -L $(SFML_DIR)\lib


$(ODIR)/%.o: %.cpp

	$(CXX) -MMD -c -o $@ $^ $(SFML_INC)

-include $(DEP)

#$(ODIR)\%.hpp: %.cpp
$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $^ $(CXXFLAGS) $(SFML_INC) -I . $(SFML_LIB) $(LIBS)

info:
	@echo " Info..."
	@echo " SOURCES = $(SRC)"
	@echo " OBJECTS = $(OBJS)"

#	$(CXX) -c $< -o $@ 



clean:

	rm $(BIN)
