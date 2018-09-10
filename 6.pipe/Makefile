.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01pipe 02pipe 03cp
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

