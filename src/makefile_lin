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
DEPS = $(OBJ:%.o=%.d)

$(ODIR)/%.o: %.cpp

	mkdir -p $(ODIR)

	$(CXX) -MMD -c -o $@ $^ $(LDFLAGS)

-include $(DEP)


$(PROG): $(OBJS)

	$(CXX) -o $(PROG) $^ $(CXXFLAGS) $(LD) $(LDFLAGS)



clean:

	rm -f -r $(ODIR) nongravitar

	

.PHONY: clean
