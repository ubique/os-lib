all: build run

rebuild: clean build

build:
	mkdir build && cd build && cmake ../ && make

run:
	./build/main

clean:
	rm -rf build