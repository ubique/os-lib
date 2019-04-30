COMPILER = g++
STATIC = helper
MAIN = main
DYNAMIC1 = dynamic1.cpp
DYNAMIC2 = dynamic2.cpp

all: libstatic.a libdynamic1.so libdynamic2.so
	$(COMPILER) $(MAIN).cpp -L. -lstatic -ldynamic1 -ldynamic2 -o ${MAIN} -ldl

libstatic.a:
	$(COMPILER) -c $(STATIC).cpp -o $(STATIC).o
	ar rcs libstatic.a $(STATIC).o

libdynamic1.so:
	$(COMPILER) -fPIC -shared $(DYNAMIC1) -o libdynamic1.so

libdynamic2.so:
	$(COMPILER) -fPIC -shared $(DYNAMIC2) -o libdynamic2.so

run:
	LD_LIBRARY_PATH=".:$$LD_LIBRARY_PATH" ./main

clean:
	rm -rf *.o *.a *.so $(MAIN)