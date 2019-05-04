BUILD_DIR=build
SOURCE_DIR=src
.PHONY: clean all


all: libsample
	./libsample

$(shell   mkdir -p $(BUILD_DIR))


#static library
${BUILD_DIR}/libfirst_supplier.a: ${SOURCE_DIR}/first_supplier.cpp
	g++ -c $^ -o $(@D)/first_supplier.o
	ar rcs $@ $(@D)/first_supplier.o


#dynamic library - compile-time linkage
${BUILD_DIR}/libsecond_supplier.so: ${SOURCE_DIR}/second_supplier.cpp
	g++ -fPIC -shared $^ -o $@


#dynamic library - runtime linkage
${BUILD_DIR}/libthird_supplier.so: ${SOURCE_DIR}/third_supplier.cpp
	g++ -fPIC -shared $^ -o $@


libsample: ${BUILD_DIR}/libfirst_supplier.a ${BUILD_DIR}/libsecond_supplier.so ${BUILD_DIR}/libthird_supplier.so ${SOURCE_DIR}/main.cpp
	g++ ${SOURCE_DIR}/main.cpp ${BUILD_DIR}/libfirst_supplier.a -Wl,-rpath ${BUILD_DIR} -L${BUILD_DIR} -lsecond_supplier -ldl -o $@


clean: 
	rm -rf ${BUILD_DIR} libsample
