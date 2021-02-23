CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
LIBS = 
SOURCES = jeopardy.c questions.c players.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = jeopardy
.PHONY: clean help

jeopardy : $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

cleanup:
	rm -f $(OBJECTS) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  clean:  removes .o and .exe files"
