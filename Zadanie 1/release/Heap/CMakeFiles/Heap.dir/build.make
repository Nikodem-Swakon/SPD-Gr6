# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release"

# Include any dependencies generated for this target.
include Heap/CMakeFiles/Heap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Heap/CMakeFiles/Heap.dir/compiler_depend.make

# Include the progress variables for this target.
include Heap/CMakeFiles/Heap.dir/progress.make

# Include the compile flags for this target's objects.
include Heap/CMakeFiles/Heap.dir/flags.make

Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o: Heap/CMakeFiles/Heap.dir/flags.make
Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o: ../Heap/Src/Heap.cpp
Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o: Heap/CMakeFiles/Heap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o -MF CMakeFiles/Heap.dir/Src/Heap.cpp.o.d -o CMakeFiles/Heap.dir/Src/Heap.cpp.o -c "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Heap/Src/Heap.cpp"

Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Heap.dir/Src/Heap.cpp.i"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Heap/Src/Heap.cpp" > CMakeFiles/Heap.dir/Src/Heap.cpp.i

Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Heap.dir/Src/Heap.cpp.s"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Heap/Src/Heap.cpp" -o CMakeFiles/Heap.dir/Src/Heap.cpp.s

# Object files for target Heap
Heap_OBJECTS = \
"CMakeFiles/Heap.dir/Src/Heap.cpp.o"

# External object files for target Heap
Heap_EXTERNAL_OBJECTS =

Heap/libHeap.a: Heap/CMakeFiles/Heap.dir/Src/Heap.cpp.o
Heap/libHeap.a: Heap/CMakeFiles/Heap.dir/build.make
Heap/libHeap.a: Heap/CMakeFiles/Heap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libHeap.a"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && $(CMAKE_COMMAND) -P CMakeFiles/Heap.dir/cmake_clean_target.cmake
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Heap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Heap/CMakeFiles/Heap.dir/build: Heap/libHeap.a
.PHONY : Heap/CMakeFiles/Heap.dir/build

Heap/CMakeFiles/Heap.dir/clean:
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" && $(CMAKE_COMMAND) -P CMakeFiles/Heap.dir/cmake_clean.cmake
.PHONY : Heap/CMakeFiles/Heap.dir/clean

Heap/CMakeFiles/Heap.dir/depend:
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Heap" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Heap/CMakeFiles/Heap.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Heap/CMakeFiles/Heap.dir/depend

