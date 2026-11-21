add_executable(bell_reference bell_reference.cpp)
target_link_libraries(bell_reference PRIVATE qpp_headers)
target_compile_options(bell_reference PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(bell_reference_test bell_reference_test.cpp)
target_link_libraries(bell_reference_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(bell_reference_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(bell_reference_test)
