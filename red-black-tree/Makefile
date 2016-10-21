CC := clang
CFLAGS := -g -Wall -std=gnu99 -gdwarf-3 -ftapir
LDFLAGS := -lrt -lm -lcilkrts

# You may add new files to the list of COMMON_SRC below
COMMON_SRC := rb_tree.c
COMMON_HEADERS := fasttime.h rb_tree.h
TARGET := rb_tree_test

ifeq ($(DEBUG),1)
CFLAGS := -DDEBUG -O0 $(CFLAGS)
else
CFLAGS := -O3 -DNDEBUG $(CFLAGS)
endif
CFLAGS := $(CFLAGS)

all: $(TARGET)

rb_tree_test: rb_tree_test.c $(COMMON_SRC) $(COMMON_HEADERS) Makefile
	$(CC) rb_tree_test.c $(COMMON_SRC) $(CFLAGS) $(LDFLAGS) -o rb_tree_test

clean::
	rm -f ./sort *.std* *.gcov *.gcda *.gcno default.profraw

