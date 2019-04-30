main: main.o libStatic.a libLinking.so libLoading.so
	g++ main.o -L. -lStatic -L. -lLinking -Wl,-rpath,. -ldl -o $@

libStatic.a: static.o
	ar rcs $@ $<

libLinking.so: linking.o
	g++ -shared -o $@ $<

libLoading.so: loading.o
	g++ -shared -o $@ $<

main.o: main.cpp
	g++ -c $< -o $@

static.o: staticLibrary/charToNumCypher.cpp staticLibrary/charToNumCypher.h
	g++ -c $< -o $@

linking.o: dynamicLinkingLibrary/CaesarCypher.cpp dynamicLinkingLibrary/CaesarCypher.h
	g++ -fPIC -c $< -o $@

loading.o: dynamicLoadingLibrary/ROT1Cypher.cpp dynamicLoadingLibrary/ROT1Cypher.h
	g++ -fPIC -c $< -o $@

clean:
	rm -rf main *.a *.o *.so

