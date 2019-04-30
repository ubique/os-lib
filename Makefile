CXXFLAGS+=-std=c++14 -Wall -O2
CXX=g++
BUILD=build

.PHONY: all run clean

all: make_dir main.cpp $(BUILD)/libhello_name.a $(BUILD)/libdynamic1.so $(BUILD)/libdynamic2.so
	$(CXX) main.cpp -L$(BUILD) -lhello_name -ldynamic1 -ldynamic2 -o main -ldl

make_dir:
	mkdir -p $(BUILD)

$(BUILD)/libhello_name.a: hello_name.cpp
	$(CXX) -c hello_name.cpp -o $(BUILD)/hello_name.o
	ar rcs $(BUILD)/libhello_name.a $(BUILD)/hello_name.o

$(BUILD)/libdynamic1.so: dynamic1.cpp
	$(CXX) -fPIC -shared dynamic1.cpp -o $(BUILD)/libdynamic1.so

$(BUILD)/libdynamic2.so: dynamic2.cpp
	$(CXX) -fPIC -shared dynamic2.cpp -o $(BUILD)/libdynamic2.so

run:
	LD_LIBRARY_PATH="$(BUILD):$$LD_LIBRARY_PATH" ./main

clean:
	rm -rf *.o *.a *.so main