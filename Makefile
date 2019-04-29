.PHONY: clean all

program: lib.o libst_prime.a libdyn_linked_bin_pow.so libdyn_loaded_gcd.so
	g++ lib.o libst_prime.a -L. -ldyn_linked_bin_pow -ldl -o program

lib.o: lib.cpp
	g++ -c $< -o $@

libst_prime.a: st_prime.cpp
	g++ -o st_prime.o -c $<
	ar rcs $@ st_prime.o

libdyn_linked_bin_pow.so: dyn_linked_bin_pow.cpp
	g++ -c -fPIC -shared $< -o $@

libdyn_loaded_gcd.so: dyn_loaded_gcd.cpp
	g++ -fPIC -shared $< -o $@

clean: 
	rm -f *.o *.a *.so program

