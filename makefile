
# Define the compiler
CC=g++
# Define the compiler options
CFLAGS=-O2
# Define the linker
LINK=g++

all: FindWords

# Define the dependencies
FindWords: FindWords.o
	$(LINK) -o FindWords FindWords.o
	
FindWords.o: FindWords.cpp BinarySearchTree.h AVLTree.h
	$(CC) -c $(CFLAGS) -std=c++0x FindWords.cpp
###
clean:
	/bin/rm -f FindWords FindWords.o	
 
