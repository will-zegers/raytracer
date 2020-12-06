find_package(Catch2 REQUIRED)

set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/test/util.cc
                 ${SOURCE_FILES}
                 ${TEST_DIR}/test-color.cc
                 ${TEST_DIR}/test-hittable.cc
                 ${TEST_DIR}/test-sphere.cc
                 ${TEST_DIR}/test-ray.cc
                 ${TEST_DIR}/test-vec3.cc)

add_executable(unit-tests ${TEST_SOURCES})

target_link_libraries(unit-tests Catch2::Catch2WithMain)
