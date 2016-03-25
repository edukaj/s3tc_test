cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (s3tc_test)

set (CMAKE_CXX_STANDARD 14)

include_directories(include controlib)
file(GLOB SOURCES "src/*.cpp")

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)
find_package (GLEW REQUIRED)

include_directories($(GLEW_INCLUDE_DIRS))

add_executable(s3tc_test ${SOURCES})

target_link_libraries (s3tc_test
	${GLFW3_LIBRARY}
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES})


