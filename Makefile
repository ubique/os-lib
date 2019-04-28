.PHONY: all run clean
                                        
CC := g++
CXXFLAGS := -O3 -std=c++11 -pedantic-errors -Wall -Wextra

TARGET      := libs
STAT        := trial_division
DYNCOMPILE  := millerrabin
DYNRUNTIME  := fermat

all: $(TARGET) clean

run: 
	./libs                                                             
	
$(TARGET): $(TARGET).o $(STAT).a $(DYNCOMPILE).so $(DYNRUNTIME).so
	$(CC) $(CXXFLAGS) $< -L. -l$(STAT) -L. -l$(DYNCOMPILE) -Wl,-rpath,. -ldl -o $@
	
$(TARGET).o: $(TARGET).cpp
	$(CC) -c $< -o $@
	
$(STAT).a: $(STAT).o
	ar rcs lib$(STAT).a $<

$(STAT).o: $(STAT).cpp $(STAT).h
	$(CC) -c $< -o $@

$(DYNCOMPILE).so: $(DYNCOMPILE).o
	$(CC) -shared -o lib$(DYNCOMPILE).so $<
	
$(DYNRUNTIME).so: $(DYNRUNTIME).o
	$(CC) -shared -o lib$(DYNRUNTIME).so $<

%.o: %.cpp %.h 
	$(CC) -fPIC -c $< -o $@ 	

clean:	
	rm -rf *.o *.a
	
