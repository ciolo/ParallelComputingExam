# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/albertociolini/Desktop/Des/OpenMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DesCpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DesCpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DesCpp.dir/flags.make

CMakeFiles/DesCpp.dir/main.cpp.o: CMakeFiles/DesCpp.dir/flags.make
CMakeFiles/DesCpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DesCpp.dir/main.cpp.o"
	/usr/local/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DesCpp.dir/main.cpp.o -c /Users/albertociolini/Desktop/Des/OpenMP/main.cpp

CMakeFiles/DesCpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DesCpp.dir/main.cpp.i"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/albertociolini/Desktop/Des/OpenMP/main.cpp > CMakeFiles/DesCpp.dir/main.cpp.i

CMakeFiles/DesCpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DesCpp.dir/main.cpp.s"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/albertociolini/Desktop/Des/OpenMP/main.cpp -o CMakeFiles/DesCpp.dir/main.cpp.s

CMakeFiles/DesCpp.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DesCpp.dir/main.cpp.o.requires

CMakeFiles/DesCpp.dir/main.cpp.o.provides: CMakeFiles/DesCpp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DesCpp.dir/build.make CMakeFiles/DesCpp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DesCpp.dir/main.cpp.o.provides

CMakeFiles/DesCpp.dir/main.cpp.o.provides.build: CMakeFiles/DesCpp.dir/main.cpp.o


CMakeFiles/DesCpp.dir/des.cpp.o: CMakeFiles/DesCpp.dir/flags.make
CMakeFiles/DesCpp.dir/des.cpp.o: ../des.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DesCpp.dir/des.cpp.o"
	/usr/local/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DesCpp.dir/des.cpp.o -c /Users/albertociolini/Desktop/Des/OpenMP/des.cpp

CMakeFiles/DesCpp.dir/des.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DesCpp.dir/des.cpp.i"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/albertociolini/Desktop/Des/OpenMP/des.cpp > CMakeFiles/DesCpp.dir/des.cpp.i

CMakeFiles/DesCpp.dir/des.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DesCpp.dir/des.cpp.s"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/albertociolini/Desktop/Des/OpenMP/des.cpp -o CMakeFiles/DesCpp.dir/des.cpp.s

CMakeFiles/DesCpp.dir/des.cpp.o.requires:

.PHONY : CMakeFiles/DesCpp.dir/des.cpp.o.requires

CMakeFiles/DesCpp.dir/des.cpp.o.provides: CMakeFiles/DesCpp.dir/des.cpp.o.requires
	$(MAKE) -f CMakeFiles/DesCpp.dir/build.make CMakeFiles/DesCpp.dir/des.cpp.o.provides.build
.PHONY : CMakeFiles/DesCpp.dir/des.cpp.o.provides

CMakeFiles/DesCpp.dir/des.cpp.o.provides.build: CMakeFiles/DesCpp.dir/des.cpp.o


CMakeFiles/DesCpp.dir/utils.cpp.o: CMakeFiles/DesCpp.dir/flags.make
CMakeFiles/DesCpp.dir/utils.cpp.o: ../utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DesCpp.dir/utils.cpp.o"
	/usr/local/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DesCpp.dir/utils.cpp.o -c /Users/albertociolini/Desktop/Des/OpenMP/utils.cpp

CMakeFiles/DesCpp.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DesCpp.dir/utils.cpp.i"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/albertociolini/Desktop/Des/OpenMP/utils.cpp > CMakeFiles/DesCpp.dir/utils.cpp.i

CMakeFiles/DesCpp.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DesCpp.dir/utils.cpp.s"
	/usr/local/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/albertociolini/Desktop/Des/OpenMP/utils.cpp -o CMakeFiles/DesCpp.dir/utils.cpp.s

CMakeFiles/DesCpp.dir/utils.cpp.o.requires:

.PHONY : CMakeFiles/DesCpp.dir/utils.cpp.o.requires

CMakeFiles/DesCpp.dir/utils.cpp.o.provides: CMakeFiles/DesCpp.dir/utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/DesCpp.dir/build.make CMakeFiles/DesCpp.dir/utils.cpp.o.provides.build
.PHONY : CMakeFiles/DesCpp.dir/utils.cpp.o.provides

CMakeFiles/DesCpp.dir/utils.cpp.o.provides.build: CMakeFiles/DesCpp.dir/utils.cpp.o


# Object files for target DesCpp
DesCpp_OBJECTS = \
"CMakeFiles/DesCpp.dir/main.cpp.o" \
"CMakeFiles/DesCpp.dir/des.cpp.o" \
"CMakeFiles/DesCpp.dir/utils.cpp.o"

# External object files for target DesCpp
DesCpp_EXTERNAL_OBJECTS =

DesCpp: CMakeFiles/DesCpp.dir/main.cpp.o
DesCpp: CMakeFiles/DesCpp.dir/des.cpp.o
DesCpp: CMakeFiles/DesCpp.dir/utils.cpp.o
DesCpp: CMakeFiles/DesCpp.dir/build.make
DesCpp: CMakeFiles/DesCpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable DesCpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DesCpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DesCpp.dir/build: DesCpp

.PHONY : CMakeFiles/DesCpp.dir/build

CMakeFiles/DesCpp.dir/requires: CMakeFiles/DesCpp.dir/main.cpp.o.requires
CMakeFiles/DesCpp.dir/requires: CMakeFiles/DesCpp.dir/des.cpp.o.requires
CMakeFiles/DesCpp.dir/requires: CMakeFiles/DesCpp.dir/utils.cpp.o.requires

.PHONY : CMakeFiles/DesCpp.dir/requires

CMakeFiles/DesCpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DesCpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DesCpp.dir/clean

CMakeFiles/DesCpp.dir/depend:
	cd /Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/albertociolini/Desktop/Des/OpenMP /Users/albertociolini/Desktop/Des/OpenMP /Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug /Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug /Users/albertociolini/Desktop/Des/OpenMP/cmake-build-debug/CMakeFiles/DesCpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DesCpp.dir/depend

