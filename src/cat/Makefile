CC = gcc
CFLAGS = -Wall -Werror -Wall -std=c11

all:	clean s21_cat

s21_cat.o:
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat

clean:
	rm -rf *.o s21_cat
