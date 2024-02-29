.PHONY: all clean test gcov_report debug check_leaks
SHELL := /bin/bash

CC = g++
CFLAGS = -std=c++17 -lstdc++ -Wall -Werror -Wextra
EXTRAWARN_FLAGS = -Wpedantic -Wshadow -Wuninitialized 
DEBUG_FLAG = -g
GCOVFLAG = --coverage
LDFLAGS = -lgtest
TEST_SRCS = tests.cpp

OS := $(shell uname)
ifeq ($(OS), Linux)
LDFLAGS += -lgtest_main -lpthread
endif

all: clean test

clean:
	rm -rf *.o *.a *.gcno test ./report ./*.dSYM test.info *.out *.gcda gcov_report *.info
	rm -rf tests draw.dot
	@clear

test: clean
	$(CC) $(CFLAGS) $(TEST_SRCS) -I./ -L./ $(LDFLAGS) -o test 
	./test

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAG) $(CFLAGS) $(TEST_SRCS) -I./ -L./ $(LDFLAGS) -o test
	./test
	lcov -t test -o test.info -c -d . --no-external
	genhtml test.info -o report
	
debug:
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ $(LDFLAGS) -o debug.out -ggdb3

check_leaks: clean debug
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./debug.out
else
	valgrind -q --tool=memcheck --leak-check=full --leak-resolution=med ./debug.out
endif
