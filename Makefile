BUILD_DIR=build
SOURCE_DIR=src
.PHONY: directories clean
.SILENT: directories


all: directories libsample
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${BUILD_DIR} ./libsample


directories:
	mkdir -p ${BUILD_DIR}


#static library
${BUILD_DIR}/libfirst_supplier.a: ${SOURCE_DIR}/first_supplier.cpp
	g++ -c ${SOURCE_DIR}/first_supplier.cpp -o ${BUILD_DIR}/first_supplier.o
	ar rcs ${BUILD_DIR}/libfirst_supplier.a ${BUILD_DIR}/first_supplier.o


#dynamic library - compile-time linkage
${BUILD_DIR}/libsecond_supplier.so: ${SOURCE_DIR}/second_supplier.cpp
	g++ -fPIC -shared ${SOURCE_DIR}/second_supplier.cpp -o ${BUILD_DIR}/libsecond_supplier.so


#dynamic library - runtime linkage
${BUILD_DIR}/libthird_supplier.so: ${SOURCE_DIR}/third_supplier.cpp
	g++ -fPIC -shared ${SOURCE_DIR}/third_supplier.cpp -o ${BUILD_DIR}/libthird_supplier.so


libsample: ${BUILD_DIR}/libfirst_supplier.a ${BUILD_DIR}/libsecond_supplier.so ${BUILD_DIR}/libthird_supplier.so ${SOURCE_DIR}/main.cpp
	g++ ${SOURCE_DIR}/main.cpp ${BUILD_DIR}/libfirst_supplier.a -L${BUILD_DIR} -lsecond_supplier -ldl -o libsample


clean: 
	rm -rf build libsample
