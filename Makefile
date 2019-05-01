all: compile libStatic.a libDynamicFirst.so libDynamicSecond.so
	g++ main.o libStatic.a -o main -L. -Wl,-rpath,. -lDynamicFirst -ldl

compile: square.cpp main.cpp average.cpp printIntsVector.cpp
	g++ -c main.cpp
	g++ -c average.cpp
	g++ -c -fPIC printIntsVector.cpp
	g++ -c -fPIC square.cpp

libDynamicFirst.so:
	g++ -shared printIntsVector.o -o libDynamicFirst.so

libDynamicSecond.so:
	g++ -shared square.o -o libDynamicSecond.so

libStatic.a:
	ar rcs libStatic.a average.o

run: all
	./main

clean:
	rm -rf *.o *.so *.a main
