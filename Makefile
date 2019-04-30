CXX_COMPILER = g++
CXX_STANDART = -std=c++14


STATIC = printer
DYNAMIC = combination
LOADED = fibonacci
MAIN = main
STATIC_LIB = lib$(STATIC).a
DYNAMIC_LIB = lib$(DYNAMIC).so
LOADED_LIB = lib$(LOADED).so

main: $(MAIN).o staticLib dynamicLib loadedLib
	g++ $(MAIN).o -L. -l$(STATIC) -L. -l$(DYNAMIC) -ldl -o $@
	
staticLib: $(STATIC).o
	ar rcs $(STATIC_LIB) $<
	
dynamicLib: $(DYNAMIC).o
	$(CXX_COMPILER) -shared $< -o $(DYNAMIC_LIB)
	
loadedLib: $(LOADED).o
	$(CXX_COMPILER) -shared $< -o $(LOADED_LIB)

$(MAIN).o: $(MAIN).cpp
	$(CXX_COMPILER) $(CXX_STANDART) -c $< -o $(MAIN).o
	
$(STATIC).o: $(STATIC).cpp $(STATIC).h
	$(CXX_COMPILER) -c $< -o $@
	
%.o: %.cpp %.h
	$(CXX_COMPILER) -fPIC -c $< -o $@
	
clean:
	rm main *.a *.o *.so 