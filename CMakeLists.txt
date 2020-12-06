set(CMAKE_MINIMUM_REQUIRED 3.16)

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED})

project(raytracer)

set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/color.cc
                 ${CMAKE_SOURCE_DIR}/src/material.cc
                 ${CMAKE_SOURCE_DIR}/src/sphere.cc
                 ${CMAKE_SOURCE_DIR}/src/vec3.cc)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    include(${CMAKE_SOURCE_DIR}/cmake/test.cmake)
endif()

include_directories(include)

set(RAYTRACER_BIN raytracer)
add_executable(${RAYTRACER_BIN} ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/src/main.cc)

add_custom_target(
    image
    COMMAND ${CMAKE_BINARY_DIR}/${RAYTRACER_BIN} > ${CMAKE_BINARY_DIR}/image.ppm
    DEPENDS ${RAYTRACER_BIN})
