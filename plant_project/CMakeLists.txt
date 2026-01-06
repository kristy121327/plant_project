cmake_minimum_required(VERSION 3.20)
project(plant_project)

include(CTest)      
enable_testing()     

add_subdirectory(src)
add_subdirectory(tests)