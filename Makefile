all:
	gcc -Wall --pedantic -ggdb src/*.c -o bin/saper
	./bin/saper
test:
	gcc -Wall --pedantic src/minefield.c src/minefield.h src/io.c src/io.h tests/minefieldtest.c -o tests/bin/testminefield
	gcc -Wall --pedantic src/minefield.c src/minefield.h src/io.c src/io.h tests/iotest.c -o tests/bin/iotest
	./tests/bin/testminefield
	./tests/bin/iotest
