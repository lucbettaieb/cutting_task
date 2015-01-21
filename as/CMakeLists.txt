cmake_minimum_required(VERSION 2.8.3)
project(as)

find_package(catkin_simple REQUIRED)

catkin_simple()

# example boost usage
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(yaml-cpp REQUIRED)
link_directories(${yaml-cpp_LIBRARY_DIRS})
include_directories(${yaml-cpp_INCLUDE_DIR})

# C++0x support - not quite the same as final C++11!
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_BUILD_TYPE Release)
# Libraries
# cs_add_library(my_lib src/my_lib.cpp)   

# Executables
# cs_add_executable(example src/example.cpp)
cs_add_executable(ppac src/ppac.cpp)
cs_add_executable(ppas src/ppas.cpp)
# target_link_library(example my_lib)
target_link_libraries(ppac ${yaml-cpp_LIBRARY})
target_link_libraries(ppas ${yaml-cpp_LIBRARY})
cs_install()
cs_export()
    
