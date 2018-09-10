.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01exec 02exec 03exec 04exec 05exec hello
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

