CC = gcc
CFLAGS = -Wall -Werror -Wall -std=c11 -D_GNU_SOURCE

all:	clean s21_grep

s21_grep.o:
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep

clean:
	rm -rf *.o s21_grep
