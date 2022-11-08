add_library(100_2_6x6 100_products_of_2_nxn_mats.cc)
target_compile_definitions(100_2_6x6 PRIVATE N=6)
target_link_libraries(100_2_6x6 PRIVATE ctme)
set_target_properties(100_2_6x6 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_2_9x9 100_products_of_2_nxn_mats.cc)
target_compile_definitions(100_2_9x9 PRIVATE N=9)
target_link_libraries(100_2_9x9 PRIVATE ctme)
set_target_properties(100_2_9x9 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_2_12x12 100_products_of_2_nxn_mats.cc)
target_compile_definitions(100_2_12x12 PRIVATE N=12)
target_link_libraries(100_2_12x12 PRIVATE ctme)
set_target_properties(100_2_12x12 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_2_15x15 100_products_of_2_nxn_mats.cc)
target_compile_definitions(100_2_15x15 PRIVATE N=15)
target_link_libraries(100_2_15x15 PRIVATE ctme)
set_target_properties(100_2_15x15 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_2_4x4 100_products_of_n_4x4_mats.cc)
target_compile_definitions(100_2_4x4 PRIVATE N=2)
target_link_libraries(100_2_4x4 PRIVATE ctme)
set_target_properties(100_2_4x4 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_3_4x4 100_products_of_n_4x4_mats.cc)
target_compile_definitions(100_3_4x4 PRIVATE N=3)
target_link_libraries(100_3_4x4 PRIVATE ctme)
set_target_properties(100_3_4x4 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_4_4x4 100_products_of_n_4x4_mats.cc)
target_compile_definitions(100_4_4x4 PRIVATE N=4)
target_link_libraries(100_4_4x4 PRIVATE ctme)
set_target_properties(100_4_4x4 PROPERTIES RULE_LAUNCH_COMPILE "time -v")

add_library(100_5_4x4 100_products_of_n_4x4_mats.cc)
target_compile_definitions(100_5_4x4 PRIVATE N=5)
target_link_libraries(100_5_4x4 PRIVATE ctme)
set_target_properties(100_5_4x4 PROPERTIES RULE_LAUNCH_COMPILE "time -v")