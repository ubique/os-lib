GCC = g++
PROD_DIR = out
STATIC = $(PROD_DIR)/static.a
LINK_DYN = $(PROD_DIR)/libfirstDynamic.so
LOAD_DYN = $(PROD_DIR)/libsecondDynamic.so
GCC_BIBL = $(GCC) -shared
GCC_OBJ = $(GCC) -c

all: $(PROD_DIR) main.o $(STATIC) $(LINK_DYN) $(LOAD_DYN)
	$(GCC) -o main -L./$(PROD_DIR) -Wl,-rpath,./$(PROD_DIR) main.o -lfirstDynamic -ldl $(STATIC)
	rm -rf main *.o

out:
	mkdir out

main.o: main.cpp
	$(GCC_OBJ) -o $@ $<

$(STATIC): multiplication.o
	ar rvs $@ $<

multiplication.o: static/multiplication.cpp static/multiplication.h
	$(GCC_OBJ) -o $@ $<

$(LINK_DYN): logarithm.o
	$(GCC_BIBL) $^ -o $@

logarithm.o: firstDynamic/logarithm.cpp firstDynamic/logarithm.h
	$(GCC_OBJ) -fPIC -o $@ $<

$(LOAD_DYN): exponentiation.o
	$(GCC_BIBL) $^ -o $@

exponentiation.o: secondDynamic/exponentiation.cpp secondDynamic/exponentiation.h
	$(GCC_OBJ) -fPIC -o $@ $<

clean:
	rm -rf out
