CC=gcc
CFLAGS=-I../ -Wall -g 
#CFLAGS=-std=c99 -O3
LDFLAGS=-lm

SRC=joe.c
OBJ=$(SRC:.c=.o)
OUT=graphiCALL

all:$(OUT)

graphiCALL: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

unit:unit.o
	$(CC) $(LDFLAGS) -o $@ $^

run:
	LD_LIBRARY_PATH=$(HOME)/opt/lib/ ./graphiCALL ../dots/tests_1.dot

clean:
	rm -rf graphiCALL *.o

veryclean:
	rm -rf graphiCALL *.o main.h joe.c

.SILENT: clean veryclean
