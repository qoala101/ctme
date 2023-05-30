find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

add_executable(unittests
  debug_logger.cc
  evaluate_cell.cc
  evaluate_to_array.cc
  evaluate_to_container.cc
  evaluate_to_vector.cc
  mat_product.cc
  mat_sum.cc
  mat.cc
  result_traits.cc
)

target_link_libraries(unittests
  PRIVATE
  GTest::gtest
  GTest::gtest_main
)

# Has to come after linking to GTest and before other libs.
# Otherwise tests in third-party libs would also be discovered.
gtest_discover_tests(unittests)

target_link_libraries(unittests
  PRIVATE
  ctme
)