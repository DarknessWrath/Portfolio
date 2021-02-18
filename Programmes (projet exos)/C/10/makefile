CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic
LDFLAGS =
objects = array.o meteobin_misc.o
executable = meteobin_misc

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clean
	tar -zcf "$(CURDIR).tar.gz" *.c *.h makefile

array.o: array.c array.h
meteobin_misc.o: meteobin_misc.c array.h
