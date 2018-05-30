# Program name
NAME = Robust.a
# Compiler command
CC = g++-6

# The root directory of headers
IDIR = .

# The root directory of the includes
ODIR = .

# Include Params
IPRMS = $(INC:%=-I%)

# Compile Flags
CFLAGS=-I $(IDIR) -std=c++11 -lpthread -Wall

# Linker Flags
LFLAGS = -pthread

DEPS = $(shell find . -name '*.cpp')
OBJECTS = $(DEPS:.cpp=.o)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.cpp $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

# Cleans up object files
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
