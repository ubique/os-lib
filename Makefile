CC = cc
STATIC = static_lib
LINK_DYN = first_dynamic_lib
LOAD_DYN = second_dynamic_lib
PROG = hw4

all: libstatic.a libdynamic_first.so libdynamic_second.so 
	$(CC) main.c -o $(PROG) -L. -lstatic -ldynamic_first -ldynamic_second -Wl,-rpath,. -ldl

libdynamic_first.so: $(LINK_DYN).o
	$(CC) -shared -o libdynamic_first.so $(LINK_DYN).o

libdynamic_second.so: $(LOAD_DYN).o 
	$(CC) -shared -o libdynamic_second.so $(LOAD_DYN).o

libstatic.a: $(STATIC).o
	ar rcs libstatic.a $(STATIC).o

$(STATIC).o: $(STATIC).c
	$(CC) -c $(STATIC).c 

$(LINK_DYN).o: $(LINK_DYN).c
	$(CC) -fPIC -c $(LINK_DYN).c 

$(LOAD_DYN).o: $(LOAD_DYN).c
	$(CC) -fPIC -c $(LOAD_DYN).c
	
clean: 
	rm -f *.o *.a *.so $(PROG)

run: all
	./$(PROG)