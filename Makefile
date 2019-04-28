#!/usr/bin/env make -f
GREATER_LIB := greater# static lib
USERGREATER_LIB := usergreater# shared lib
TETRATION_LIB := tetration# dynamic linked shared lib

.PHONY: all clean

all: main

main: main.o lib$(GREATER_LIB).a lib$(USERGREATER_LIB).so lib$(TETRATION_LIB).so
	$(CC) $< -L. -l$(GREATER_LIB) -L. -l$(USERGREATER_LIB) -Wl,-rpath,. -ldl -o $@

main.o : main.c
	$(CC) -c $< -o $@

lib$(GREATER_LIB).a: $(GREATER_LIB).o
	$(AR) rcs $@ $^

$(GREATER_LIB).o: $(GREATER_LIB).c $(GREATER_LIB).h
	$(CC) -c $< -o $@

lib$(USERGREATER_LIB).so: $(USERGREATER_LIB).o
	$(CC) -shared $^ -o $@

$(USERGREATER_LIB).o: $(USERGREATER_LIB).c $(USERGREATER_LIB).h
	$(CC) -fPIC -c $< -o $@

lib$(TETRATION_LIB).so: $(TETRATION_LIB).o
	$(CC) -shared $^ -o $@

$(TETRATION_LIB).o: $(TETRATION_LIB).c $(TETRATION_LIB).h
	$(CC) -fPIC -c $< -o $@

clean:
	rm -rf *.o *.a *.so main
