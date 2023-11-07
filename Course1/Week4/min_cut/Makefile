# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := -ggdb3 -O0 -Wall -lm

# add header files here
HDRS := inc/min_cut.h ../../../c_structures/inc/c_structures.h

# define main file (used for clean function, in order to build, use make MAIN=<dir>/<file>.c)
MAIN := main/min_cut.c
# add source files here
SRCS := $(wildcard src/*.c) $(wildcard ../../../c_structures/src/*.c) $(MAIN) 

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
# FILENAME := $(notdir $(MAIN))
EXEC := a.out

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
# $(OBJS): $(@:.o=.c) $(HDRS) Makefile
# 	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# $(OBJDIR)/%.o: %.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# recipe to clean the workspace
ALL_EXECS = a.out
clean:
	rm -f $(ALL_EXECS) $(OBJS)

.PHONY: all clean