CC = gcc
LDFLAGS = -Wall -Wextra -Werror -std=c11
CFLAGS = -c
TEST = test

all: clean test linter cppcheck

rebuild: clean all

test: cat_test grep_test

cat_test: s21_cat
	sh cat/test.sh

grep_test: s21_grep
	sh grep/test.sh

s21_cat:
	$(CC) cat/$@.c $(LDFLAGS) -o cat/$@

s21_grep:
	$(CC) grep/$@.c $(LDFLAGS) -D_GNU_SOURCE -o grep/$@

clean:
	rm -rf cat/*.o grep/*.o cat/s21_cat grep/s21_grep cat/*result.txt grep/*result.txt

linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c cat/*.c
	python3 ../materials/linters/cpplint.py --extensions=h cat/*.h
	python3 ../materials/linters/cpplint.py --extensions=c grep/*.c
	python3 ../materials/linters/cpplint.py --extensions=h grep/*.h
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem cat/*.c
	cppcheck --enable=all --suppress=missingIncludeSystem grep/*.c