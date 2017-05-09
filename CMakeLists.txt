cmake_minimum_required(VERSION 2.8)

# C is used for test in OpenGL
project(models C CXX)

include(ExternalProject)

set(GL2PS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/gl2ps")
set(GL2PS_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gl2ps-prefix")

ExternalProject_Add(gl2ps
  SOURCE_DIR "${GL2PS_SOURCE}"
  PREFIX     "${GL2PS_PREFIX}"
  CMAKE_COMMAND "${CMAKE_COMMAND}"
  CMAKE_CACHE_ARGS "-DCMAKE_INSTALL_PREFIX:path=${GL2PS_PREFIX}")

include_directories("${GL2PS_PREFIX}/include")
add_library(gl2ps-lib STATIC IMPORTED)
set_property(TARGET gl2ps-lib PROPERTY
  IMPORTED_LOCATION "${GL2PS_PREFIX}/lib/libgl2ps.a")
add_dependencies(gl2ps-lib gl2ps)

add_library(common STATIC common.cpp)
target_link_libraries(common gl2ps-lib)
set_target_properties(common PROPERTIES COMPILE_FLAGS "-std=c++11")

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS gl glu)

add_executable(arb arb.cpp)
target_link_libraries(arb common ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${PNG_LIBRARY} ${ZLIB_LIBRARY})
set_target_properties(arb PROPERTIES COMPILE_FLAGS "-std=c++11")
