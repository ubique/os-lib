EXECUTABLE = lib

all: $(EXECUTABLE)

$(EXECUTABLE): main.o static dynamicLinked dynamicLoaded
	g++ main.o -L. -ldigitsSum -L. -lgcd -ldl -o $@

static: digitsSum.o
	ar rcs libdigitsSum.a $<

dynamicLinked: dynamicLinkedGcd.o
	g++ -shared $< -o libgcd.so

dynamicLoaded: dynamicLoadedFactor.o
	g++ -shared $< -o libfactorization.so

main.o: main.cpp
	g++ -std=c++11 -c $< -o main.o

digitsSum.o: staticDigitsSum.cpp staticDigitsSum.h
	g++ -c $< -o $@

%.o: %.cpp %.h
	g++ -fPIC -c $< -o $@

clean:
	rm $(EXECUTABLE) *.a *.o *.so