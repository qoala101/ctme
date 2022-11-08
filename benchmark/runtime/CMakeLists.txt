find_package(benchmark REQUIRED)

add_executable(benchmarks
  product_of_2_nxn_array_mats.cc
  product_of_2_nxn_vector_mats.cc
  product_of_n_4x4_array_mats.cc
  product_of_n_4x4_vector_mats.cc
)

target_link_libraries(benchmarks
  PRIVATE ctme
  PRIVATE benchmark::benchmark
)