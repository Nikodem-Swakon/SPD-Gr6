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
include Task/CMakeFiles/Task.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Task/CMakeFiles/Task.dir/compiler_depend.make

# Include the progress variables for this target.
include Task/CMakeFiles/Task.dir/progress.make

# Include the compile flags for this target's objects.
include Task/CMakeFiles/Task.dir/flags.make

Task/CMakeFiles/Task.dir/src/Task.cpp.o: Task/CMakeFiles/Task.dir/flags.make
Task/CMakeFiles/Task.dir/src/Task.cpp.o: ../Task/src/Task.cpp
Task/CMakeFiles/Task.dir/src/Task.cpp.o: Task/CMakeFiles/Task.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Task/CMakeFiles/Task.dir/src/Task.cpp.o"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Task/CMakeFiles/Task.dir/src/Task.cpp.o -MF CMakeFiles/Task.dir/src/Task.cpp.o.d -o CMakeFiles/Task.dir/src/Task.cpp.o -c "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Task/src/Task.cpp"

Task/CMakeFiles/Task.dir/src/Task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task.dir/src/Task.cpp.i"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Task/src/Task.cpp" > CMakeFiles/Task.dir/src/Task.cpp.i

Task/CMakeFiles/Task.dir/src/Task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task.dir/src/Task.cpp.s"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Task/src/Task.cpp" -o CMakeFiles/Task.dir/src/Task.cpp.s

# Object files for target Task
Task_OBJECTS = \
"CMakeFiles/Task.dir/src/Task.cpp.o"

# External object files for target Task
Task_EXTERNAL_OBJECTS =

Task/libTask.a: Task/CMakeFiles/Task.dir/src/Task.cpp.o
Task/libTask.a: Task/CMakeFiles/Task.dir/build.make
Task/libTask.a: Task/CMakeFiles/Task.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTask.a"
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && $(CMAKE_COMMAND) -P CMakeFiles/Task.dir/cmake_clean_target.cmake
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Task.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Task/CMakeFiles/Task.dir/build: Task/libTask.a
.PHONY : Task/CMakeFiles/Task.dir/build

Task/CMakeFiles/Task.dir/clean:
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" && $(CMAKE_COMMAND) -P CMakeFiles/Task.dir/cmake_clean.cmake
.PHONY : Task/CMakeFiles/Task.dir/clean

Task/CMakeFiles/Task.dir/depend:
	cd "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/Task" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task" "/Users/asialalala/Documents/Studia/semestr 6/SPD/SPD-Gr6/Zadanie 1/release/Task/CMakeFiles/Task.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Task/CMakeFiles/Task.dir/depend

