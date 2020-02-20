# CMakeList.txt : CMake project for BitshiftersHackaton, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add source to this project's executable.
add_executable (BitshiftersHackaton "BitshiftersHackaton.cpp" "BitshiftersHackaton.h")

target_link_libraries("BitshiftersHackaton" ${OpenCV_LIBS} )
# TODO: Add tests and install targets if needed.
