.PHONY: all
all: mdir libst.a libdyn2.so libdyn1.so runnable

mdir:
	mkdir -p tmp

libst.a: st.h st.cpp mdir
	g++ -c st.cpp -o tmp/libst.o
	ar rvs tmp/libst.a tmp/libst.o

libdyn2.so: dyn2.h dyn2.cpp mdir
	g++ -shared dyn2.h dyn2.cpp -o tmp/libdyn2.so

libdyn1.so: dyn1.h dyn1.cpp mdir
	g++ -shared dyn1.h dyn1.cpp -o tmp/libdyn1.so

runnable: main.cpp libst.a libdyn2.so libdyn1.so mdir
	g++ main.cpp -lstdc++ -ldl tmp/libdyn1.so tmp/libst.a -o tmp/os_lib

.PHONY: run

run:
	./tmp/os_lib

.PHONY: clean

clean:
	rm tmp/*
	rmdir tmp
