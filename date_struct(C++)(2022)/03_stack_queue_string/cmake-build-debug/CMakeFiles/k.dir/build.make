# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\ProgrameFiles\Cmake\bin\cmake.exe

# The command to remove a file.
RM = E:\ProgrameFiles\Cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/k.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/k.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/k.dir/flags.make

CMakeFiles/k.dir/kmp.cpp.obj: CMakeFiles/k.dir/flags.make
CMakeFiles/k.dir/kmp.cpp.obj: ../kmp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/k.dir/kmp.cpp.obj"
	"E:\Program Files\CLion 2021.3.2\bin\mingw\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\k.dir\kmp.cpp.obj -c E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\kmp.cpp

CMakeFiles/k.dir/kmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k.dir/kmp.cpp.i"
	"E:\Program Files\CLion 2021.3.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\kmp.cpp > CMakeFiles\k.dir\kmp.cpp.i

CMakeFiles/k.dir/kmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k.dir/kmp.cpp.s"
	"E:\Program Files\CLion 2021.3.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\kmp.cpp -o CMakeFiles\k.dir\kmp.cpp.s

# Object files for target k
k_OBJECTS = \
"CMakeFiles/k.dir/kmp.cpp.obj"

# External object files for target k
k_EXTERNAL_OBJECTS =

k.exe: CMakeFiles/k.dir/kmp.cpp.obj
k.exe: CMakeFiles/k.dir/build.make
k.exe: CMakeFiles/k.dir/linklibs.rsp
k.exe: CMakeFiles/k.dir/objects1.rsp
k.exe: CMakeFiles/k.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable k.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\k.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/k.dir/build: k.exe

.PHONY : CMakeFiles/k.dir/build

CMakeFiles/k.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\k.dir\cmake_clean.cmake
.PHONY : CMakeFiles/k.dir/clean

CMakeFiles/k.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug E:\ujs_meng\Shuju_struct_c++\03_stack_queue_string\cmake-build-debug\CMakeFiles\k.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/k.dir/depend
