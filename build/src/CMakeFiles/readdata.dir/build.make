# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/beyza/working/csvRead

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beyza/working/csvRead/build

# Include any dependencies generated for this target.
include src/CMakeFiles/readdata.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/readdata.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/readdata.dir/flags.make

src/CMakeFiles/readdata.dir/main.cpp.o: src/CMakeFiles/readdata.dir/flags.make
src/CMakeFiles/readdata.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beyza/working/csvRead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/readdata.dir/main.cpp.o"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/readdata.dir/main.cpp.o -c /home/beyza/working/csvRead/src/main.cpp

src/CMakeFiles/readdata.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readdata.dir/main.cpp.i"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beyza/working/csvRead/src/main.cpp > CMakeFiles/readdata.dir/main.cpp.i

src/CMakeFiles/readdata.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readdata.dir/main.cpp.s"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beyza/working/csvRead/src/main.cpp -o CMakeFiles/readdata.dir/main.cpp.s

src/CMakeFiles/readdata.dir/plot.cpp.o: src/CMakeFiles/readdata.dir/flags.make
src/CMakeFiles/readdata.dir/plot.cpp.o: ../src/plot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beyza/working/csvRead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/readdata.dir/plot.cpp.o"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/readdata.dir/plot.cpp.o -c /home/beyza/working/csvRead/src/plot.cpp

src/CMakeFiles/readdata.dir/plot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readdata.dir/plot.cpp.i"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beyza/working/csvRead/src/plot.cpp > CMakeFiles/readdata.dir/plot.cpp.i

src/CMakeFiles/readdata.dir/plot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readdata.dir/plot.cpp.s"
	cd /home/beyza/working/csvRead/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beyza/working/csvRead/src/plot.cpp -o CMakeFiles/readdata.dir/plot.cpp.s

# Object files for target readdata
readdata_OBJECTS = \
"CMakeFiles/readdata.dir/main.cpp.o" \
"CMakeFiles/readdata.dir/plot.cpp.o"

# External object files for target readdata
readdata_EXTERNAL_OBJECTS =

src/readdata: src/CMakeFiles/readdata.dir/main.cpp.o
src/readdata: src/CMakeFiles/readdata.dir/plot.cpp.o
src/readdata: src/CMakeFiles/readdata.dir/build.make
src/readdata: /usr/lib/x86_64-linux-gnu/libpython3.8.so
src/readdata: src/CMakeFiles/readdata.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beyza/working/csvRead/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable readdata"
	cd /home/beyza/working/csvRead/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readdata.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/readdata.dir/build: src/readdata

.PHONY : src/CMakeFiles/readdata.dir/build

src/CMakeFiles/readdata.dir/clean:
	cd /home/beyza/working/csvRead/build/src && $(CMAKE_COMMAND) -P CMakeFiles/readdata.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/readdata.dir/clean

src/CMakeFiles/readdata.dir/depend:
	cd /home/beyza/working/csvRead/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beyza/working/csvRead /home/beyza/working/csvRead/src /home/beyza/working/csvRead/build /home/beyza/working/csvRead/build/src /home/beyza/working/csvRead/build/src/CMakeFiles/readdata.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/readdata.dir/depend

