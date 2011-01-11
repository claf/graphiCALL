CC=gcc
CFLAGS=-I../ -Wall -g $(shell pkg-config --cflags kaapi)
#CFLAGS=-std=c99 -O3 $(shell pkg-config --cflags kaapi)
LDFLAGS=$(shell pkg-config --libs kaapi) -lpthread -lm

SRC=joe.c boot.c
OBJ=$(SRC:.c=.o)
OUT=graphiCALL

all:$(OUT)

graphiCALL: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

joe.c:../cecilia_version/src/graphiCALL/joe.c
	cecilia2xkaapi.pl ../cecilia_version/src/graphiCALL/*.c

run:
	LD_LIBRARY_PATH=$(HOME)/opt/lib/ ./graphiCALL ../dots/tests_1.dot

clean:
	rm -rf graphiCALL *.o

veryclean:
	rm -rf graphiCALL *.o main.h joe.c

.SILENT: clean veryclean
