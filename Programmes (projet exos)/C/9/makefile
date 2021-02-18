CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wno-unused-parameter
LDFLAGS = -lm
objects = double_base.o double_poly.o main.o
executable = pgame

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clean
	tar -zcf "$(CURDIR).tar.gz" *.c *.h makefile

double_base.o: double_base.c double_base.h
double_poly.o: double_poly.c double_poly.h double_base.h
main.o: main.c double_poly.h
