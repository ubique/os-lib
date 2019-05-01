CXX = g++
CXX_STANDARD = -std=c++14

STATIC = greeting
DYNAMIC = fibonacci
LOADED = palindrome
MAIN = main
STATIC_LIB = lib$(STATIC).a
DYNAMIC_LIB = lib$(DYNAMIC).so
LOADED_LIB = lib$(LOADED).so

all: main

run: main
	./main

main: $(MAIN).o $(STATIC_LIB) $(DYNAMIC_LIB) $(LOADED_LIB)
	g++ $(MAIN).o -L. -l$(STATIC) -L. -l$(DYNAMIC) -ldl -o $@

$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXX_STANDARD) -c $< -o $(MAIN).o

$(STATIC_LIB): $(STATIC).o
	ar rcs $(STATIC_LIB) $<

$(DYNAMIC_LIB): $(DYNAMIC).o
	$(CXX) -shared $< -o $(DYNAMIC_LIB)

$(LOADED_LIB): $(LOADED).o
	$(CXX) -shared $< -o $(LOADED_LIB)

$(STATIC).o: $(STATIC).cpp $(STATIC).h
	$(CXX) -c $< -o $@

# For dynamic libs
%.o: %.cpp %.h
	$(CXX) -fPIC -c $< -o $@

.PONY: clean
clean:
	rm main *.a *.o *.so
