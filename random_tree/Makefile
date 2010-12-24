CC=gcc
CFLAGS=-std=c99 -Wall -g
LDFLAGS=-ligraph
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OUT=tree

all:$(OUT)

tree: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

run:
	./tree test.dot

clean:
	rm -rf tree *.o

veryclean:
	rm -rf tree *.o *.dot

.SILENT: clean veryclean
