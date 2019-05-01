BUILD_DIR=./build
SOURCE_DIR=./src

all: directories launcher
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${BUILD_DIR} ./launcher

directories:
	mkdir ${BUILD_DIR}

${BUILD_DIR}/libstaticCompile.a: ${SOURCE_DIR}/staticCompile.cpp
	g++ -c ${SOURCE_DIR}/staticCompile.cpp -o ${BUILD_DIR}/staticCompile.o
	ar rcs ${BUILD_DIR}/libstaticCompile.a ${BUILD_DIR}/staticCompile.o

${BUILD_DIR}/libsharedCompile.so: ${SOURCE_DIR}/sharedCompile.cpp
	g++ -fPIC -shared ${SOURCE_DIR}/sharedCompile.cpp -o ${BUILD_DIR}/libsharedCompile.so

${BUILD_DIR}/libsharedRuntime.so: ${SOURCE_DIR}/sharedRuntime.cpp
	g++ -fPIC -shared ${SOURCE_DIR}/sharedRuntime.cpp -o ${BUILD_DIR}/libsharedRuntime.so

launcher: ${BUILD_DIR}/libstaticCompile.a ${BUILD_DIR}/libsharedCompile.so ${BUILD_DIR}/libsharedRuntime.so ${SOURCE_DIR}/main.cpp
	g++ ${SOURCE_DIR}/main.cpp ${BUILD_DIR}/libstaticCompile.a -L${BUILD_DIR} -lsharedCompile -ldl -o launcher

clean: 
	rm -rf build launcher
