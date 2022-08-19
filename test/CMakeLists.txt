find_package(GTest REQUIRED)

include(CTest)
include(GoogleTest)

enable_testing()

add_executable(tests
  evaluate_cell.cc
  evaluate_to_array.cc
  evaluate_to_container.cc
  evaluate_to_vector.cc
  mat_product.cc
  mat_sum.cc
  mat.cc
  result_traits.cc)

target_link_libraries(tests PRIVATE ctme)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(tests)