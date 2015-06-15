COMPILER = gcc
SOURCES = main.h main.c comp.c
LONG_FLAGS = -Wall -Wextra -g -std=c1x
SHORT_FLAGS = -g -std=c1x -w
OUTPUT = psvm.out

all: build arm fire

build:
	${COMPILER} ${SOURCES} ${SHORT_FLAGS} -o ${OUTPUT}

arm:
	chmod a+x psvm.out

fire:
	mv psvm.out ../bin/psvm.out

careful:
	${COMPILER} ${SOURCES} ${LONG_FLAGS} -o {OUTPUT}

clean:
	rm -rf *.o build
	clear
	ls
