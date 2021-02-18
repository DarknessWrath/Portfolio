CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wno-unused-parameter
LDFLAGS =
objects = fnat.o main.o
executable = cgame

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clean
	tar -zcf "$(CURDIR).tar.gz" *.c *.h makefile

fnat.o: fnat.c fnat.h nat.h
main.o: main.c nat.h fnat.h
