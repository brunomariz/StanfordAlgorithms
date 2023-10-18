# A simple Makefile for compiling small C projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := 

# add header files here
HDRS := 

# define main file (used for clean function, in order to build, use make MAIN=<dir>/<file>.c)
MAIN := merge_sort.c
# add source files here
SRCS := $(MAIN) 

# TEST_SRCS := $(filter-out $(MAIN),$(SRCS)) tests/test.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# TEST_OBJS := $(TEST_SRCS:.c=.o)

# name of executable
EXEC := a.out

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# test: $(TEST_OBJS) $(HDRS) Makefile
# 	$(CC) -o $@ $(TEST_OBJS) $(CFLAGS)


# recipe for building object files
# $(OBJS): $(@:.o=.c) $(HDRS) Makefile
# 	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# $(OBJDIR)/%.o: %.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# recipe to clean the workspace
clean:
	rm -f test $(EXEC) $(OBJS) $(TEST_OBJS)

.PHONY: all clean