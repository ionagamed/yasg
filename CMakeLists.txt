cmake_minimum_required(VERSION 2.6)
project(yasg)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH bin)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -g")
else()
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11")
endif()

file(GLOB files src/*.cpp)
add_executable(yasg ${files})

find_package(SFML 2 REQUIRED COMPONENTS graphics system window network)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(yasg ${SFML_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(yasg ${OPENGL_gl_LIBRARY})
