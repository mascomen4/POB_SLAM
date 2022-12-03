cmake_minimum_required(VERSION 3.20)
project(optimization_robot_localization)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/eigen3)

#set(Ceres_DIR "/home/pi/libs/ceres-solver-2.1.0/build")

#find_package(CXSparse REQUIRED)

find_package(Ceres REQUIRED)

set(Pangolin_DIR /home/pi/work_drivecast/slams/thirdparty/Pangolin-master/build)

find_package(Pangolin REQUIRED)

add_library(POB_SLAM
        src/InteractionHelper.cpp include/InteractionHelper.h
        src/Optimizer.cpp include/Optimizer.h
        src/Viz.cpp include/Viz.h
        src/RobotInterface.cpp include/RobotInterface.h
        src/Control.cpp include/Control.h
        src/Localizer.cpp include/Localizer.h
        src/Sensor.cpp include/Sensor.h
        include/SystemTypes.h)
target_link_libraries(POB_SLAM PUBLIC ${Pangolin_LIBRARIES} Ceres::ceres)
target_include_directories(POB_SLAM PUBLIC ${Pangolin_INCLUDE_DIRS})
#include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(optimization_robot_localization main.cpp)
target_link_libraries(optimization_robot_localization Ceres::ceres)

add_executable(test test.cpp)
target_link_libraries(test Ceres::ceres)