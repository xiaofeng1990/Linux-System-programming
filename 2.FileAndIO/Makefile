.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01fileno 02open 03cp 04lseek 05hole 06ls 07stat 08ls-l 09dup
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

