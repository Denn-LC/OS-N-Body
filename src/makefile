CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c17

all:
	$(CC) $(CFLAGS) main.c -o main

run: all
	main.exe

clean:
	del /Q main.exe 2>nul || exit 0