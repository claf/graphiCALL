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
	./tree test.dot && dot -Tpng test.dot -o test.png

clean:
	rm -rf tree *.o *.dot *.png

.SILENT: clean veryclean
