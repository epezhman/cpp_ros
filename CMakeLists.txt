cmake_minimum_required (VERSION 2.8.7)
project (CppProject)

set(CMAKE_AUTOMOC ON)

#set(CMAKE_MODULE_PATH "/home/milad/Documents/eigen/cmake")
find_package(Eigen3 REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(EIGEN3_INCLUDE_DIR ${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(CppProject Part2.cpp Volume.cpp MHDHandler.cpp SourceDetectorPair.cpp GetRay.cpp EntryPoint.cpp RayTracing.cpp OnTheFlySystemMx.cpp RenderPaint.cpp window.cpp TransferFunction.cpp)
#add_executable(Part2 ReadCSV.cpp Volume.cpp MHDHandler.cpp) 

add_definitions(-std=c++11) #c++11 for MHD handler

target_link_libraries(CppProject ${Qt5Widgets_LIBRARIES})
