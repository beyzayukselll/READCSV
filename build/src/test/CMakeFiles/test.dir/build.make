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
CMAKE_SOURCE_DIR = /home/bcd/programming/least_square_identification

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bcd/programming/least_square_identification/build/src

# Include any dependencies generated for this target.
include test/CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test.dir/flags.make

test/CMakeFiles/test.dir/__/src/Data.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/Data.cpp.o: ../../src/Data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test.dir/__/src/Data.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/Data.cpp.o -c /home/bcd/programming/least_square_identification/src/Data.cpp

test/CMakeFiles/test.dir/__/src/Data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/Data.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/Data.cpp > CMakeFiles/test.dir/__/src/Data.cpp.i

test/CMakeFiles/test.dir/__/src/Data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/Data.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/Data.cpp -o CMakeFiles/test.dir/__/src/Data.cpp.s

test/CMakeFiles/test.dir/__/src/frequency.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/frequency.cpp.o: ../../src/frequency.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/test.dir/__/src/frequency.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/frequency.cpp.o -c /home/bcd/programming/least_square_identification/src/frequency.cpp

test/CMakeFiles/test.dir/__/src/frequency.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/frequency.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/frequency.cpp > CMakeFiles/test.dir/__/src/frequency.cpp.i

test/CMakeFiles/test.dir/__/src/frequency.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/frequency.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/frequency.cpp -o CMakeFiles/test.dir/__/src/frequency.cpp.s

test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.o: ../../src/leastsquareid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/leastsquareid.cpp.o -c /home/bcd/programming/least_square_identification/src/leastsquareid.cpp

test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/leastsquareid.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/leastsquareid.cpp > CMakeFiles/test.dir/__/src/leastsquareid.cpp.i

test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/leastsquareid.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/leastsquareid.cpp -o CMakeFiles/test.dir/__/src/leastsquareid.cpp.s

test/CMakeFiles/test.dir/__/src/read.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/read.cpp.o: ../../src/read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/CMakeFiles/test.dir/__/src/read.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/read.cpp.o -c /home/bcd/programming/least_square_identification/src/read.cpp

test/CMakeFiles/test.dir/__/src/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/read.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/read.cpp > CMakeFiles/test.dir/__/src/read.cpp.i

test/CMakeFiles/test.dir/__/src/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/read.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/read.cpp -o CMakeFiles/test.dir/__/src/read.cpp.s

test/CMakeFiles/test.dir/__/src/signal.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/signal.cpp.o: ../../src/signal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object test/CMakeFiles/test.dir/__/src/signal.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/signal.cpp.o -c /home/bcd/programming/least_square_identification/src/signal.cpp

test/CMakeFiles/test.dir/__/src/signal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/signal.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/signal.cpp > CMakeFiles/test.dir/__/src/signal.cpp.i

test/CMakeFiles/test.dir/__/src/signal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/signal.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/signal.cpp -o CMakeFiles/test.dir/__/src/signal.cpp.s

test/CMakeFiles/test.dir/__/src/torquesignal.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/torquesignal.cpp.o: ../../src/torquesignal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object test/CMakeFiles/test.dir/__/src/torquesignal.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/torquesignal.cpp.o -c /home/bcd/programming/least_square_identification/src/torquesignal.cpp

test/CMakeFiles/test.dir/__/src/torquesignal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/torquesignal.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/torquesignal.cpp > CMakeFiles/test.dir/__/src/torquesignal.cpp.i

test/CMakeFiles/test.dir/__/src/torquesignal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/torquesignal.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/torquesignal.cpp -o CMakeFiles/test.dir/__/src/torquesignal.cpp.s

test/CMakeFiles/test.dir/__/src/write.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/__/src/write.cpp.o: ../../src/write.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object test/CMakeFiles/test.dir/__/src/write.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/__/src/write.cpp.o -c /home/bcd/programming/least_square_identification/src/write.cpp

test/CMakeFiles/test.dir/__/src/write.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/__/src/write.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/src/write.cpp > CMakeFiles/test.dir/__/src/write.cpp.i

test/CMakeFiles/test.dir/__/src/write.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/__/src/write.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/src/write.cpp -o CMakeFiles/test.dir/__/src/write.cpp.s

test/CMakeFiles/test.dir/read_test.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/read_test.cpp.o: ../../test/read_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object test/CMakeFiles/test.dir/read_test.cpp.o"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/read_test.cpp.o -c /home/bcd/programming/least_square_identification/test/read_test.cpp

test/CMakeFiles/test.dir/read_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/read_test.cpp.i"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bcd/programming/least_square_identification/test/read_test.cpp > CMakeFiles/test.dir/read_test.cpp.i

test/CMakeFiles/test.dir/read_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/read_test.cpp.s"
	cd /home/bcd/programming/least_square_identification/build/src/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bcd/programming/least_square_identification/test/read_test.cpp -o CMakeFiles/test.dir/read_test.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/__/src/Data.cpp.o" \
"CMakeFiles/test.dir/__/src/frequency.cpp.o" \
"CMakeFiles/test.dir/__/src/leastsquareid.cpp.o" \
"CMakeFiles/test.dir/__/src/read.cpp.o" \
"CMakeFiles/test.dir/__/src/signal.cpp.o" \
"CMakeFiles/test.dir/__/src/torquesignal.cpp.o" \
"CMakeFiles/test.dir/__/src/write.cpp.o" \
"CMakeFiles/test.dir/read_test.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test/test: test/CMakeFiles/test.dir/__/src/Data.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/frequency.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/leastsquareid.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/read.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/signal.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/torquesignal.cpp.o
test/test: test/CMakeFiles/test.dir/__/src/write.cpp.o
test/test: test/CMakeFiles/test.dir/read_test.cpp.o
test/test: test/CMakeFiles/test.dir/build.make
test/test: /usr/lib/x86_64-linux-gnu/libpython3.8.so
test/test: test/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bcd/programming/least_square_identification/build/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable test"
	cd /home/bcd/programming/least_square_identification/build/src/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test.dir/build: test/test

.PHONY : test/CMakeFiles/test.dir/build

test/CMakeFiles/test.dir/clean:
	cd /home/bcd/programming/least_square_identification/build/src/test && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test.dir/clean

test/CMakeFiles/test.dir/depend:
	cd /home/bcd/programming/least_square_identification/build/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bcd/programming/least_square_identification /home/bcd/programming/least_square_identification/test /home/bcd/programming/least_square_identification/build/src /home/bcd/programming/least_square_identification/build/src/test /home/bcd/programming/least_square_identification/build/src/test/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test.dir/depend

