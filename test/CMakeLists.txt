find_package(GTest REQUIRED)
# find_package(benchmark REQUIRED)

include(CTest)
include(GoogleTest)

enable_testing()

add_executable(tests run_time_tests.cc)

target_link_libraries(tests PRIVATE ctmm)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
# target_link_libraries(tests PRIVATE benchmark::benchmark)

gtest_discover_tests(tests)