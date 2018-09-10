.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01fork 05atexit 09waite 10system
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

