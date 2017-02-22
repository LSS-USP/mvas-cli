# Project directories
SRCDIR := src
INCDIR := include
BINDIR := bin
OBJDIR := obj

# Targets with main code inside
TARGETS := bin/mvas

# Required flags
CC := gcc
CCFLAGS := -Wall -lpthread -std=gnu11
INCLUDES := -I./$(INCDIR)/
#DEBUG := -D_DEBUG_
DEBUG :=

# Files to process
SRCFILES := $(shell find -name '*.c' -printf '%P ')
OBJFILES := $(basename $(subst $(SRCDIR),$(OBJDIR),$(SRCFILES)))

all: prepare $(TARGETS)

$(TARGETS): $(OBJFILES:%=%.o)
	$(CC) $(CCFLAGS) $^ -o $@ $(DEBUG)

$(OBJDIR)/%.o: $(basename $(subst $(OBJDIR),$(SRCDIR),$(OBJDIR)/%.o)).c
	$(CC) -o $@ -c $< $(INCLUDES) $(CCFLAGS) $(DEBUG)

.PHONY: clean, prepare

prepare:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
