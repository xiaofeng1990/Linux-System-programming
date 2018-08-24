.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01fcntl 02fcntl 03fcntl
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

