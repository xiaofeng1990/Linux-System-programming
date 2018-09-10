.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01signal 02signal 03kill 04pause 05alarm 06reentrant 07sigstaus 08sigactin 09sigaction_recv 10sigqueue_send 11setitimer
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

