# Compiler command
CC = g++

# The root directory of headers
IDIR = ./include

# The root directory of the includes
ODIR = .

# Include Params
IPRMS = $(INC:%=-I%)

# Compile Flags
CFLAGS=-I $(IDIR) -std=c++14 -lpthread -Wall

# Linker Flags
LFLAGS = -pthread

HEADERS = $(shell find ./include -name '*.h')

# All singlefile tests: A quick macro for making test cases
TESTNAMES = task-manager socket-server robot

DEPS = $(shell find ./core -name '*.cpp') $(shell find ./util -name '*.cpp')
OBJECTS = $(DEPS:.cpp=.o)

Robust.a: $(OBJECTS)  
	ar rcs Robust.a $(OBJECTS)

Tests: $(TESTNAMES);

$(TESTNAMES): Robust.a
	g++ -o ./tests/$@/$@ ./tests/$@/$@.cpp ./Robust.a $(CFLAGS) $(LFLAGS) 


%.o: %.cpp $(DEPS) $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

# Cleans up object files
.PHONY: clean
clean:
	rm $(OBJECTS)

