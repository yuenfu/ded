CFLAGS = -Wall -Wextra -pedantic
LIBNAME = capstone

all: ded

ded: main.o core.o
	${CC} ${CFLAGS} $^ -l$(LIBNAME) -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o ded