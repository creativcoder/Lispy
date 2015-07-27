CC=gcc
CFLAGS=-Wall
parsing: parsing.c mpc.c
	$(CC) -std=c99 $(CFLAGS) parsing.c mpc.c -ledit -lm -o parsing
