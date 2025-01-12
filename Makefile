all:
	gcc -Wall --pedantic -ggdb src/*.c -o bin/saper
	./bin/saper
