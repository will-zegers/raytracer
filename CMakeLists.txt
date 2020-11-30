set(CMAKE_MINIMUM_REQUIRED 3.16)

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED})

project(raytracer)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    include(${CMAKE_SOURCE_DIR}/cmake/test.cmake)
endif()

set(RAYTRACER_BIN raytracer)
include_directories(include)
add_executable(${RAYTRACER_BIN} src/main.cc)

add_custom_target(
    image
    COMMAND ${CMAKE_BINARY_DIR}/${RAYTRACER_BIN} > ${CMAKE_BINARY_DIR}/image.ppm
    DEPENDS ${RAYTRACER_BIN})
