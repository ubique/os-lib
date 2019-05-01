CXX := g++
OPTIONS := -std=c++17 -Wall -pedantic

all: run

clean:
	rm *.o *.a *.so medley || echo "Nothing to clean"

run: medley libfile.so
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:." ./medley

medley: medley.o libhello.a libbottles.so
	$(CXX) $(OPTIONS) medley.o libhello.a libbottles.so -L . -l hello -l bottles -l dl -o medley

libhello.a: hello.o
	ar rcs libhello.a hello.o

libbottles.so:
	$(CXX) -shared -fPIC $(OPTIONS) bottles.cpp -o libbottles.so

libfile.so:
	$(CXX) -shared -fPIC $(OPTIONS) file.cpp -o libfile.so

hello.o:
	$(CXX) $(OPTIONS) -c hello.cpp

medley.o:
	$(CXX) $(OPTIONS) -c medley.cpp
