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
	./tree -l 4 -k 10 -n 10 -c 4 -f test && dot -Tpng *.dot -O

clean:
	rm -rf tree *.o *.dot *.png

.SILENT: clean veryclean
