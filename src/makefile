CXX = g++

# HIGHLY RECOMMENDED flags
CXXFLAGS += -Wall -Wextra -g -ggdb

PROG = nongravitar

ODIR  = ../obj

# required for SFML programs
LD := $(shell pkg-config sfml-all --libs)
LDFLAGS := -g -ggdb

# The rest will turn any source file ending in .cpp
# into a program of the same name

SRC := $(wildcard *.cpp)
OBJS = $(addprefix $(ODIR)/,$(SRC:.cpp=.o))


$(ODIR)/%.o: %.cpp

	mkdir -p $(ODIR)

	$(CXX) -c -o $@ $^ $(LDFLAGS)



$(PROG): $(OBJS)

	$(CXX) -o $(PROG) $^ $(CXXFLAGS) $(LD) $(LDFLAGS)



clean:

	rm -f $(ODIR)/*.o nongravitar

	

.PHONY: clean
