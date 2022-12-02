cmake_minimum_required(VERSION 3.20)
project(optimization_robot_localization)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/eigen3)

#set(Ceres_DIR "/home/pi/libs/ceres-solver-2.1.0/build")

#find_package(CXSparse REQUIRED)

find_package(Ceres REQUIRED)

add_executable(optimization_robot_localization main.cpp)
target_link_libraries(optimization_robot_localization Ceres::ceres)

add_executable(test test.cpp)
target_link_libraries(test Ceres::ceres)