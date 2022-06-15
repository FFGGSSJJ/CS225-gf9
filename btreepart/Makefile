CC = g++ -std=c++11
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean 4_bTree.o btree

4_bTree.o: 4_bTree.h
	${CC} ${CFLAGS} -c 4_bTree.cpp
btree: 4_bTree.o
	${CC} ${CFLAGS} 4_bTree.o ${LDFLAGS} -o btree
clean:
	rm -rf *.o
	rm -rf btree