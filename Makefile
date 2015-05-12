
###################################################
# VARIABLES
###################################################

# Project name
# -------------------------------------------------
NAME=ironsh

# Commands
# -------------------------------------------------
CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -std=c11
DEBUGGER=gdb
RM=rm -rf

# Directories
# -------------------------------------------------
BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

# Files
# -------------------------------------------------
BIN=$(BINDIR)/$(NAME)
SRC:=$(wildcard $(SRCDIR)/*.c)
LIBMY_PRINTF=$(wildcard $(LIBDIR)/my_printf/*.c)


###################################################
# COMMON TARGETS
###################################################


# Default target
# -------------------------------------------------
all: $(NAME)


# Directories
# -------------------------------------------------
$(BINDIR):
  mkdir -p $(BINDIR)


# Removes binary file
# -------------------------------------------------
clean:
  $(RM) $(BIN)


# Removes binary file & launches compiling
# -------------------------------------------------
re: clean all


###################################################
# MINISHELL TARGETS
###################################################


# Compiling
# -------------------------------------------------
$(NAME): $(BINDIR)
  $(CC) $(CFLAGS) $(SRC) -o $(BIN)


###################################################
# LIBS TARGETS
###################################################


# my_printf lib compiling
# -------------------------------------------------
libmy_printf:
  $(CC) $(CFLAGS) -shared -o $(LIBMY_PRINTF) $(OBJDIR)/*.o
