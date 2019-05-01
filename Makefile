BUILD_DIR := $(shell pwd)/build
GCC := g++
TARGET := main
CXXFLAGS := -O2 -std=c++11
BUILD = build

$(shell mkdir -p $(BUILD_DIR))

.PHONY: all run clean

all: $(BUILD_DIR)/main run

run:
	LD_LIBRARY_PATH=$(BUILD_DIR) $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/libpoint_geometry.a $(BUILD_DIR)/libintersections.so $(BUILD_DIR)/libfigures_geometry.so
	$(GCC) $(CXXFLAGS) $(BUILD_DIR)/main.o -L$(BUILD_DIR) -lpoint_geometry -L$(BUILD_DIR) -lintersections -L$(BUILD_DIR) -lfigures_geometry -ldl -o $(BUILD_DIR)/main

$(BUILD_DIR)/main.o: main.cpp
	$(GCC) $(CXXFLAGS) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/libpoint_geometry.a: $(BUILD_DIR)/point_geometry.o
	ar rcs $(BUILD_DIR)/libpoint_geometry.a $(BUILD_DIR)/point_geometry.o

$(BUILD_DIR)/libfigures_geometry.so: $(BUILD_DIR)/figures_geometry.o
	$(GCC) $(CXXFLAGS) -shared $(BUILD_DIR)/figures_geometry.o -o $(BUILD_DIR)/libfigures_geometry.so

$(BUILD_DIR)/libintersections.so: $(BUILD_DIR)/intersections.o $(BUILD_DIR)/point_geometry.o
	$(GCC) $(CXXFLAGS) -shared $(BUILD_DIR)/intersections.o $(BUILD_DIR)/point_geometry.o -o $(BUILD_DIR)/libintersections.so

$(BUILD_DIR)/point_geometry.o: point_geometry.h point_geometry.cpp
	$(GCC) $(CXXFLAGS) -c -fPIC point_geometry.cpp -o $(BUILD_DIR)/point_geometry.o

$(BUILD_DIR)/figures_geometry.o: figures_geometry.h figures_geometry.cpp
	$(GCC) $(CXXFLAGS) -c -fPIC figures_geometry.cpp -o $(BUILD_DIR)/figures_geometry.o

$(BUILD_DIR)/intersections.o: intersections.h intersections.cpp
	$(GCC) $(CXXFLAGS) -c -fPIC intersections.cpp -o $(BUILD_DIR)/intersections.o

clean:
	rm -rf $(BUILD_DIR)