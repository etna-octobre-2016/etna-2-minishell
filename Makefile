###################################################
# VARIABLES
###################################################

# Project name
# -------------------------------------------------
NAME=libmy_malloc_`uname`.so
LINKNAME=libmy_malloc.so
TESTNAME=testbin

# Commands
# -------------------------------------------------
CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -std=c11
DEBUGGER=gdb
RM=rm -rf

# Directories
# -------------------------------------------------
BINDIR=./bin
SRCDIR=./src

# Files
# -------------------------------------------------
BIN=$(BINDIR)/$(NAME)
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(patsubst %.c,%.o,$(SRC))

###################################################
# TARGETS
###################################################

all:clean $(NAME)
	cd $(BINDIR); ln -s $(NAME) $(LINKNAME); cd ..

# Linking
# -------------------------------------------------
$(NAME):$(OBJ) $(BINDIR)
	$(CC) $(CFLAGS) -shared -o $(BIN) $(OBJ)

# Object files
# -------------------------------------------------
%.o:%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Directories
# -------------------------------------------------
$(BINDIR):
	mkdir -p $(BINDIR)

# Utils
# -------------------------------------------------
clean:
	$(RM) $(OBJ) $(BINDIR) $(TESTNAME)

tests: clean all
	$(CC) $(CFLAGS) -g test/main.c bin/$(NAME) -o $(TESTNAME)
	$(DEBUGGER) ./$(TESTNAME)
