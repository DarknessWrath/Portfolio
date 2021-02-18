CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic
LDFLAGS =
objects = array.o meteobin_print.o
executable = meteobin_print

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clean
	tar -zcf "$(CURDIR).tar.gz" *.c *.h makefile

array.o: array.c array.h
meteobin_print.o: meteobin_print.c array.h
