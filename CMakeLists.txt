cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (s3tc_test)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

message("CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")

include_directories(include controlib)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_definitions(-DLINUX)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (GLFW3 REQUIRED)

add_executable(s3tc_test ${SOURCES} ${HEADERS})

target_link_libraries (s3tc_test
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW3_LIBRARIES}
	)
