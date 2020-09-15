all: langfreq

SRC=langfreq.c
CC=gcc
CFLAGS=

langfreq: $(SRC)
	$(CC) $(SRC) -o $@


