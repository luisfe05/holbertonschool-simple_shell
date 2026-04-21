# Compiler to use
CC = gcc

# Flags compiler, strict warnings and C89 standard
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

# Find all .c files in the current directory
SRC = $(wildcard *.c)

# Transform the list of .c files into a list of .o files
OBJ = $(SRC:.c=.o)

# Name of the final executable file
NAME = hsh

# Default target when running 'make' with no arguments
all: $(NAME)

# Link all object files into the final executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# Compile each .c file into a .o file
# Recompile if the .c or shell.h changes
%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove generated files to clean the directory
clean:
	rm -f $(OBJ) $(NAME)

# Clean everything and rebuild from scratch
re: clean all

# These targets are not real files — prevents conflicts with files of the same name
.PHONY: all clean re