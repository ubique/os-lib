# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/miketerentyev/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/miketerentyev/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/miketerentyev/itmo/2-year/os-course/os-lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/miketerentyev/itmo/2-year/os-course/os-lib

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Users/miketerentyev/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.11.1/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/miketerentyev/itmo/2-year/os-course/os-lib/CMakeFiles /Users/miketerentyev/itmo/2-year/os-course/os-lib/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/miketerentyev/itmo/2-year/os-course/os-lib/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named os_lib

# Build rule for target.
os_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 os_lib
.PHONY : os_lib

# fast build rule for target.
os_lib/fast:
	$(MAKE) -f CMakeFiles/os_lib.dir/build.make CMakeFiles/os_lib.dir/build
.PHONY : os_lib/fast

#=============================================================================
# Target rules for targets named static-lib

# Build rule for target.
static-lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 static-lib
.PHONY : static-lib

# fast build rule for target.
static-lib/fast:
	$(MAKE) -f static-lib/CMakeFiles/static-lib.dir/build.make static-lib/CMakeFiles/static-lib.dir/build
.PHONY : static-lib/fast

#=============================================================================
# Target rules for targets named first-dynamic-lib

# Build rule for target.
first-dynamic-lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 first-dynamic-lib
.PHONY : first-dynamic-lib

# fast build rule for target.
first-dynamic-lib/fast:
	$(MAKE) -f first-dynamic-lib/CMakeFiles/first-dynamic-lib.dir/build.make first-dynamic-lib/CMakeFiles/first-dynamic-lib.dir/build
.PHONY : first-dynamic-lib/fast

#=============================================================================
# Target rules for targets named second-dynamic-lib

# Build rule for target.
second-dynamic-lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 second-dynamic-lib
.PHONY : second-dynamic-lib

# fast build rule for target.
second-dynamic-lib/fast:
	$(MAKE) -f second-dynamic-lib/CMakeFiles/second-dynamic-lib.dir/build.make second-dynamic-lib/CMakeFiles/second-dynamic-lib.dir/build
.PHONY : second-dynamic-lib/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/os_lib.dir/build.make CMakeFiles/os_lib.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/os_lib.dir/build.make CMakeFiles/os_lib.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/os_lib.dir/build.make CMakeFiles/os_lib.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... os_lib"
	@echo "... static-lib"
	@echo "... first-dynamic-lib"
	@echo "... second-dynamic-lib"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

