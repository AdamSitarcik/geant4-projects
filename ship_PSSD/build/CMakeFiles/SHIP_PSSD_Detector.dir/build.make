# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adam/skola/phd/geant4/ship_PSSD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adam/skola/phd/geant4/ship_PSSD/build

# Utility rule file for SHIP_PSSD_Detector.

# Include the progress variables for this target.
include CMakeFiles/SHIP_PSSD_Detector.dir/progress.make

CMakeFiles/SHIP_PSSD_Detector: pssd


SHIP_PSSD_Detector: CMakeFiles/SHIP_PSSD_Detector
SHIP_PSSD_Detector: CMakeFiles/SHIP_PSSD_Detector.dir/build.make

.PHONY : SHIP_PSSD_Detector

# Rule to build all files generated by this target.
CMakeFiles/SHIP_PSSD_Detector.dir/build: SHIP_PSSD_Detector

.PHONY : CMakeFiles/SHIP_PSSD_Detector.dir/build

CMakeFiles/SHIP_PSSD_Detector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SHIP_PSSD_Detector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SHIP_PSSD_Detector.dir/clean

CMakeFiles/SHIP_PSSD_Detector.dir/depend:
	cd /home/adam/skola/phd/geant4/ship_PSSD/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adam/skola/phd/geant4/ship_PSSD /home/adam/skola/phd/geant4/ship_PSSD /home/adam/skola/phd/geant4/ship_PSSD/build /home/adam/skola/phd/geant4/ship_PSSD/build /home/adam/skola/phd/geant4/ship_PSSD/build/CMakeFiles/SHIP_PSSD_Detector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SHIP_PSSD_Detector.dir/depend

