cmake_minimum_required(VERSION 2.8.3)
project(ws15cpp_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/home/epezhman/Qt/5.5/gcc_64")

set(CMAKE_AUTOMOC ON)

find_package(catkin REQUIRED COMPONENTS roscpp moveit_core moveit_ros_planning_interface geometry_msgs)

find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(nodes nodes/arm_node.cpp)

add_executable(gui gui/ros_qt.h gui/ros_qt.cpp gui/qt_node.cpp)


target_link_libraries(nodes ${catkin_LIBRARIES})

target_link_libraries(gui ${Qt5Widgets_LIBRARIES} ${catkin_LIBRARIES})

