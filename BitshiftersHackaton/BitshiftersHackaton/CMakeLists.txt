# CMakeList.txt : CMake project for BitshiftersHackaton, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(TO_NATIVE_PATH "${BitshiftersHackaton_SOURCE_DIR}/dnn/models/" MODELS_FOLDER_PATH)
add_definitions(-D_MODELS_FOLDER_PATH=R\"\"\(${MODELS_FOLDER_PATH}\)\"\")

# Add source to this project's executable.
add_executable (BitshiftersHackaton "BitshiftersHackaton.cpp" "BitshiftersHackaton.h" "YOLO.cpp" "YOLO.h" "FileLogger.cpp")

target_link_libraries("BitshiftersHackaton" ${OpenCV_LIBS} )
# TODO: Add tests and install targets if needed.
