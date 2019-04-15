CUR_PATH = $(shell pwd)

main: main.o modular_arithmetics.a combinatorics.so prime.so
	g++ main.o -L./ -lmodular_arithmetics -L${CUR_PATH} -lcombinatorics -ldl -o main
main.o: main.cpp
	g++	-c main.cpp -o main.o
modular_arithmetics.a: modular_arithmetics.o
	ar rcs libmodular_arithmetics.a modular_arithmetics.o
modular_arithmetics.o: modular_arithmetics.h modular_arithmetics.cpp
	g++ -c modular_arithmetics.cpp -o modular_arithmetics.o
combinatorics.so: combinatorics.o
	g++ -shared combinatorics.o -o libcombinatorics.so
combinatorics.o: combinatorics.h combinatorics.cpp
	g++ -c -fPIC combinatorics.cpp -o combinatorics.o
prime.so: prime.o
	gcc -shared prime.o -o libprime.so
prime.o: prime.h prime.c
	gcc -c -fPIC prime.c -o prime.o
clean:
	rm main main.o libmodular_arithmetics.a modular_arithmetics.o combinatorics.o libcombinatorics.so prime.o libprime.so
