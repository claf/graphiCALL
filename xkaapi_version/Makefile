CC=gcc
CFLAGS=-std=c99 -I../ -Wall -g $(shell pkg-config --cflags kaapi)
#CFLAGS=-std=c99 -O3 $(shell pkg-config --cflags kaapi)
LDFLAGS=$(shell pkg-config --libs kaapi) -lpthread

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OUT=graphiCALL

all:$(OUT)

graphiCALL: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

perl:
	cecilia2xkaapi.pl ../cecilia_version/src/graphiCALL/*.c

run:
	LD_LIBRARY_PATH=$(HOME)/opt/lib/ ./graphiCALL 5 4	

clean:
	rm -rf graphiCALL *.o

veryclean:
	rm -rf graphiCALL *.o main.h joe.c

.SILENT: clean veryclean
