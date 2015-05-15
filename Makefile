
###################################################
# VARIABLES
###################################################


# Binary files names
PROJECT=ironsh
LIBMY=libmy.so

# Commands
CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -std=c11
DEBUGGER=gdb
RM=rm -rf

# Directories (commons)
BINDIR=./bin
LIBDIR=./lib
SRCDIR=./src

# Directories (libmy)
LIBMY_DIR=$(LIBDIR)/my
LIBMY_BINDIR=$(LIBMY_DIR)/bin
LIBMY_SRCDIR=$(LIBMY_DIR)/src
LIBMY_OBJDIR=$(LIBMY_DIR)/obj

# Files (project)
BIN=$(BINDIR)/$(PROJECT)
SRC:=$(wildcard $(SRCDIR)/*.c)

# Files (libmy)
LIBMY_BIN=$(LIBMY_BINDIR)/$(LIBMY)
LIBMY_SRC:=$(wildcard $(LIBMY_SRCDIR)/*.c)
LIBMY_OBJ:=$(patsubst %.c,%.o,$(LIBMY_SRC))


####################################################
# MINISHELL TARGETS
####################################################


# Default target
all: $(BINDIR) $(PROJECT)

# Builds project
$(PROJECT):
	$(CC) $(CFLAGS) $(SRC) -L $(LIBMY_BINDIR) $(LIBMY_BIN) -o $(BIN)

# Removes objects files
clean:
	$(RM) $(LIBMY_OBJDIR)

# Removes objects files and binaries
fclean: clean
	$(RM) $(BINDIR) $(LIBMY_BINDIR)

# Removes all & launches compiling
re: fclean libmy all

# Creates binaries directory
$(BINDIR):
	mkdir -p $(BINDIR)


####################################################
# LIBS TARGETS
####################################################

# Generates object files (for libraries)
%.o:%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# libmy compiling
libmy: $(LIBMY_BINDIR) $(LIBMY_OBJDIR) $(LIBMY_OBJ)
	mv $(LIBMY_OBJ) $(LIBMY_OBJDIR)
	$(CC) $(CFLAGS) -shared -o $(LIBMY_BIN) $(LIBMY_OBJDIR)/*.o

$(LIBMY_BINDIR):
	mkdir -p $(LIBMY_BINDIR)

$(LIBMY_OBJDIR):
	mkdir -p $(LIBMY_OBJDIR)
