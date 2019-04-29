GCC = g++
SRC = library_sources
LIBDYNAMIC = libdynamic.so
DYNAMIC_FLAG = -shared
MAIN = main

all:  answer.o main.o static_lib.o dynamic.o dynamic_second.o
	ar rcs libstatic.a answer.o static_lib.o
	$(GCC) $(DYNAMIC_FLAG) dynamic.o -o libdynamic.so
	$(GCC) $(DYNAMIC_FLAG) dynamic_second.o -o libdynamic_second.so
	$(GCC) main.o -L. -lstatic  -L. -ldynamic -ldl -o staticallyAndDynamically-linked
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}; ./staticallyAndDynamically-linked

main.o:
	$(GCC) -c main.cpp

answer.o:
	$(GCC) -c answer.cpp

static_lib.o:
	$(GCC) -c static_lib.cpp

dynamic_second.o:
	$(GCC) -c -fPIC dynamic_second.cpp

dynamic.o:
	$(GCC) -c -fPIC dynamic.cpp

clean:
	rm -vf *.o *.a  *.so staticallyAndDynamically-linked
