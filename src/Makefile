PROGRAM   = anthill

CC        = gcc
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut -lm

SRC=$(wildcard *.c)

$(PROGRAM): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean dist

clean:
		-rm $(PROGRAM)
