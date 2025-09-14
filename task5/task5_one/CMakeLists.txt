cmake_minimum_required(VERSION 3.10)
project(RedDetector)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(red_detector red_detector.cpp)
target_link_libraries(red_detector ${OpenCV_LIBS})
