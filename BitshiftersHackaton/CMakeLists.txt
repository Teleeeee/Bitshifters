# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("BitshiftersHackaton")

# Include sub-projects.
add_subdirectory ("BitshiftersHackaton")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
