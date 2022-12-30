cmake_minimum_required(VERSION 3.00)
project(duihuanstation)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/camera)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)
add_executable(run main.cpp include/serial.h)

target_link_libraries(run ${OpenCV_LIBS})
target_link_libraries(run SRCSO)
add_library(SRCSO ${DIR_SRC})


target_link_libraries(run /lib/libMVSDK.so)