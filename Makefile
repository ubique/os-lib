BUILD_DIR = build
STATIC = libs/static/get_day.cpp
DYNAMIC1 = libs/dynamic1/get_month.cpp
DYNAMIC2 = libs/dynamic2/get_year.cpp
.PHONY: directories clean
.SILENT: directories

run:
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${BUILD_DIR} ./main

all: directories main
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${BUILD_DIR} ./main

directories:
	mkdir -p ${BUILD_DIR}


${BUILD_DIR}/libget_day.a: ${STATIC}
	g++ -c ${STATIC} -o ${BUILD_DIR}/get_day.o
	ar rcs ${BUILD_DIR}/libget_day.a ${BUILD_DIR}/get_day.o


${BUILD_DIR}/libget_month.so: $(DYNAMIC1)
	g++ -fPIC -shared ${DYNAMIC1} -o ${BUILD_DIR}/libget_month.so


${BUILD_DIR}/libget_year.so: $(DYNAMIC2)
	g++ -fPIC -shared ${DYNAMIC2} -o ${BUILD_DIR}/libget_year.so


main: ${BUILD_DIR}/libget_day.a ${BUILD_DIR}/libget_month.so ${BUILD_DIR}/libget_year.so main.cpp
	g++ main.cpp ${BUILD_DIR}/libget_day.a -L${BUILD_DIR} -lget_month -ldl -o main


clean: 
	rm -rf build main	
