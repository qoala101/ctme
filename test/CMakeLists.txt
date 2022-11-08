find_package(GTest REQUIRED)

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
  result_traits.cc
)

target_link_libraries(tests
  PRIVATE ctme
  PRIVATE GTest::gtest GTest::gtest_main
)

gtest_discover_tests(tests)