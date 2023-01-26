driver: hangman.o driver.cpp
	g++ -Wall hangman.o driver.cpp -o driver

mytest: hangman.o mytest.cpp
	g++ -Wall hangman.o mytest.cpp -o mytest

hangman.o: hangman.cpp hangman.h
	g++ -Wall -c hangman.cpp

val:
	make driver
	valgrind driver

valtest:
	make mytest
	valgrind mytest