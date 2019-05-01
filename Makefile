.PHONY: all clean run

all: libraries

run: all
	./libraries

libraries: libraries.o shared/shared_library.so static/static_library.a loadable/loadable_library.so
	g++ -std=c++17 -L. -l:./static/static_library.a -l:./shared/shared_library.so -Wl,-rpath,. -o $@ $^ -ldl
	
%.o: %.cpp
	g++ -std=c++17 -c -o $@ $^

shared/shared_library.so: shared/fibonacci.o
	g++ -std=c++17 -shared -o $@ $^

shared/%.o: shared/%.cpp
	g++ -std=c++17 -fPIC -c -o $@ $^

static/static_library.a: static/power.o
	ar rcs $@ $^
	ranlib $@

static/%.o: static/%.cpp
	g++ -std=c++17 -c -o $@ $^

loadable/loadable_library.so: loadable/factorial.o
	g++ -std=c++17 -shared -o $@ $^

loadable/%.o: loadable/%.cpp
	g++ -std=c++17 -fPIC -c -o $@ $^

clean:
	rm -rf libraries *.o
	rm -rf shared/*.so shared/*.o
	rm -rf static/*.a static/*.o
	rm -rf loadable/*.so loadable/*.o

