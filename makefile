#!/bin/makefile

CC= gcc
CFLAGS = -g -Wall -Wextra -pedantic -ansi -fPIE

EXEC = tp1

OBJDIR = obj
BINDIR = bin
SRCDIR = src

SRC = $(wildcard $(SRCDIR)/*.c)

all: $(BINDIR)/$(EXEC)
	@echo Tapez bin/$(EXEC)

$(BINDIR)/$(EXEC) : $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^
	
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $<
	
clean :
	rm -rf *.o



