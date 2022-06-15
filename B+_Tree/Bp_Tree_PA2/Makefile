CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean  BPlus_node.o BPlus_tree.o main.o program

BPlus_node.o: BPlus_node.h
	${CC} ${CFLAGS} -c BPlus_node.cpp
BPlus_tree.o: BPlus_tree.h BPlus_node.h
	${CC} ${CFLAGS} -c BPlus_tree.cpp
main.o: BPlus_tree.o
	${CC} ${CFLAGS} -c main.cpp
program: main.o
	${CC} ${CFLAGS} main.o ${LDFLAGS} -o program
clean:
	rm -rf *.o
	rm -rf program