INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= main.h
CFILES= functions.c pthreads.c main.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: main

clean:
	-rm -f *.o *.d
	-rm -f pthread
	-rm -f main

main: main.o pthreads.o functions.o
	$(CC) -o main main.o pthreads.o functions.o -I. -lpthread

main.o: main.c
	$(CC) -c -o main.o main.c -I. -lpthread

pthreads.o: pthreads.c
	$(CC) -c -o pthreads.o pthreads.c -I. -lpthread

functions.o: functions.c
	$(CC) -c -o functions.o functions.c -I. -lpthread
