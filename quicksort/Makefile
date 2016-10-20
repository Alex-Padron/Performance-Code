CC := clang
CFLAGS := -g -Wall -std=gnu99 -gdwarf-3 -ftapir
LDFLAGS := -lrt -lm -lcilkrts

# You may add new files to the list of COMMON_SRC below
COMMON_SRC := quicksort.c
COMMON_HEADERS := fasttime.h
TARGET := quicksort_test

ifeq ($(DEBUG),1)
CFLAGS := -DDEBUG -O0 $(CFLAGS)
else
CFLAGS := -O3 -DNDEBUG $(CFLAGS)
endif
CFLAGS := $(CFLAGS)

all: $(TARGET)

quicksort_test: quicksort_test.c $(COMMON_SRC) $(COMMON_HEADERS) Makefile
	$(CC) quicksort_test.c $(COMMON_SRC) $(CFLAGS) $(LDFLAGS) -o quicksort_test

clean::
	rm -f ./sort *.std* *.gcov *.gcda *.gcno default.profraw

