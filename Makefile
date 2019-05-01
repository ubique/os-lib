LIB_PATH=src
OUT_PATH=lib

CXX=g++ -std=c++14

all: main

clean:
	rm main *.o

# executable

main: main.o static.a dynamic_linkage.so dynamic_load.so
	$(CXX) $< -L. -l:./$(OUT_PATH)/static.a -l:./$(OUT_PATH)/dynamic_linkage.so -Wl,-rpath,. -ldl -o $@

main.o: main.cpp
	$(CXX) -c $^ -o $@

# static library

static.o: $(LIB_PATH)/static.cpp $(LIB_PATH)/static.hpp
	$(CXX) -c $< -o $@

static.a: static.o
	ar rcs $(OUT_PATH)/$@ $<

# dynamic linking library

dynamic_linkage.o: $(LIB_PATH)/dynamic_linkage.cpp $(LIB_PATH)/dynamic_linkage.hpp
	$(CXX) -fPIC -c $< -o $@

dynamic_linkage.so: dynamic_linkage.o
	$(CXX) -shared $< -o $(OUT_PATH)/$@

# dynamic load librari

dynamic_load.o: $(LIB_PATH)/dynamic_load.cpp $(LIB_PATH)/dynamic_load.hpp
	$(CXX) -fPIC -c $< -o $@

dynamic_load.so: dynamic_load.o
	$(CXX) -shared $< -o $(OUT_PATH)/$@