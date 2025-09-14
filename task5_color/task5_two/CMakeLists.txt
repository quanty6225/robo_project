cmake_minimum_required(VERSION 3.10)
project(RuneDetector)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rune_detector rune_detector.cpp)
target_link_libraries(rune_detector ${OpenCV_LIBS})
