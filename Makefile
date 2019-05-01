CXX = g++
CXX_STANDARD = -std=c++14

DIR = out
STATIC = greeting
DYNAMIC = fibonacci
LOADED = palindrome
MAIN = main
STATIC_LIB = lib$(STATIC).a
DYNAMIC_LIB = lib$(DYNAMIC).so
LOADED_LIB = lib$(LOADED).so

all: main

run: main
	LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(DIR)" ./main $(SEARCH_AT)

main: $(DIR)/$(MAIN).o $(DIR)/$(STATIC_LIB) $(DIR)/$(DYNAMIC_LIB) $(DIR)/$(LOADED_LIB)
	$(CXX) $(DIR)/$(MAIN).o -L $(DIR) -l$(STATIC) -l$(DYNAMIC) -ldl -o $@

$(DIR)/$(STATIC_LIB): $(DIR)/$(STATIC).o
	ar rcs $@ $<

$(DIR)/lib%.so: $(DIR)/%.o
	$(CXX) -shared $< -o $@

$(DIR)/$(DYNAMIC_LIB): $(DIR)/$(DYNAMIC).o
	$(CXX) -shared $< -o $@

$(DIR)/$(LOADED_LIB): $(DIR)/$(LOADED).o
	$(CXX) -shared $< -o $@

$(DIR)/$(MAIN).o: $(MAIN).cpp
	mkdir -p $(DIR)
	$(CXX) $(CXX_STANDARD) -c $< -o $@

$(DIR)/$(STATIC).o: $(STATIC).cpp $(STATIC).h
	mkdir -p $(DIR)
	$(CXX) -c $< -o $@

# For dynamic libs
$(DIR)/%.o: %.cpp %.h
	mkdir -p $(DIR)
	$(CXX) -fPIC -c $< -o $@

.PHONY: clean
clean:
	rm -r $(DIR)
	rm $(MAIN)
