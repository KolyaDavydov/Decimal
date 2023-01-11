
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
LDFLAGS=
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
LIBSOURCES=decimal_utils.c decimal_convertor.c decimal_arithmetic.c decimal_comparison.c decimal_other.c decstr.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: gcov_report

s21_decimal.a: $(LIBOBJECTS)
	ar -crs s21_decimal.a $(LIBOBJECTS)
	rm -f *.o

test: tests.c s21_decimal.a
	$(CC) $(CFLAGS) tests.c $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

valgrind:
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBSOURCES) test_valgrind.c s21_decimal.h decstr.h -o vtests_run
	sh valgrind.sh ./vtests_run

# docker_test:
# 	sh ./run.sh

rebuild: clean all

clean:
	rm -rf *.o \
		*.a \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		report.info
