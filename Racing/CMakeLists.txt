cmake_minimum_required(VERSION 3.10)
project(Racing)

set(CMAKE_CXX_STANDARD 11)

configure_file(images/1.png images/1.png COPYONLY)
configure_file(images/2.png images/2.png COPYONLY)
configure_file(images/3.png images/3.png COPYONLY)
configure_file(images/4.png images/4.png COPYONLY)
configure_file(images/5.png images/5.png COPYONLY)
configure_file(images/6.png images/6.png COPYONLY)
configure_file(images/7.png images/7.png COPYONLY)
configure_file(images/bg.png images/bg.png COPYONLY)
# Define sources and executable
set(EXECUTABLE_NAME "Racing")

add_executable(${EXECUTABLE_NAME} main.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()