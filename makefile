#!/bin/makefile

CC= gcc
CFLAGS = -g -Wall -Wextra -pedantic -ansi -no-pie -fno-pie

EXEC = tp1

OBJDIR = obj
BINDIR = bin
SRCDIR = src

SRC = $(wildcard $(SRCDIR)/*.c)

all: $(BINDIR)/$(EXEC)
	@echo Tapez ./bin/$(EXEC) \<fichier bibliotheque\> \<fichier création emprunt\> \<fichier suppression emprunt\>

$(BINDIR)/$(EXEC) : $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^
	
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $<
	
clean :
	rm -rf *.o



