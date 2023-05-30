cmake_minimum_required(VERSION 3.18)

option(BUILD_TESTS "Whether to build tests.")
option(BUILD_BENCHMARKS "Whether to build benchmarks including the compile time ones.")

if(BUILD_TESTS OR BUILD_BENCHMARKS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

project(
  "ctme"
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(ctme INTERFACE)
target_include_directories(ctme INTERFACE .)

if(BUILD_TESTS)
  target_compile_options(ctme
    INTERFACE
    -fprofile-instr-generate
    -fcoverage-mapping
  )

  target_link_options(ctme
    INTERFACE
    -fprofile-instr-generate
    -fcoverage-mapping
  )

  include(CTest)
  add_subdirectory(test)
endif()

if(BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()