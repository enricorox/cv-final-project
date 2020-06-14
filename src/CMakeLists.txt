cmake_minimum_required(VERSION 2.8)
project(final-project)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(find-tree find-tree.cpp seeker.cpp seeker.h preprocess.h)
add_executable(preprocess preprocess.cpp preprocess.h)

target_link_libraries(find-tree ${OpenCV_LIBS})
target_link_libraries(preprocess ${OpenCV_LIBS})