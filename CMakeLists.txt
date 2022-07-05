project(bitgen CXX)
cmake_minimum_required(VERSION 3.0)

option(BITGEN_BUILD_TESTS "Build BitGen tests" OFF)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif (NOT CMAKE_CXX_STANDARD)

set(BITGEN_INCLUDE_DIRS 
    "${PROJECT_SOURCE_DIR}/include/"
    CACHE INTERNAL 
    "BITGEN_INCLUDE_DIRS")

add_library(bitgen STATIC 
    "${PROJECT_SOURCE_DIR}/src/bit_generator.cc")
target_include_directories(bitgen PUBLIC 
    "${BITGEN_INCLUDE_DIRS}")

if (BITGEN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(third_party/googletest)

    add_executable(bitgen_tests 
        "${PROJECT_SOURCE_DIR}/src/bit_generator_test.cc"
        "${PROJECT_SOURCE_DIR}/src/bit_generator.cc")
    target_link_libraries(bitgen_tests 
        bitgen gtest gtest_main)

    include(GoogleTest)
    gtest_discover_tests(bitgen_tests PROPERTIES DISCOVERY_TIMEOUT 30)
endif (BITGEN_BUILD_TESTS)
