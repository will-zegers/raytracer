cmake_minimum_required(VERSION 3.16)

project(raytracer)

find_package(Catch2 REQUIRED)

set(RAYTRACER_BIN raytracer)
include_directories(include)
add_executable(${RAYTRACER_BIN} src/main.cc)

add_custom_target(
    image
    COMMAND ${CMAKE_BINARY_DIR}/${RAYTRACER_BIN} > ${CMAKE_BINARY_DIR}/image.ppm
    DEPENDS ${RAYTRACER_BIN})
