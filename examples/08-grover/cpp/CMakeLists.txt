add_executable(grover grover.cpp)
target_link_libraries(grover PRIVATE qpp_headers)
target_compile_options(grover PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(grover_test grover_test.cpp)
target_link_libraries(grover_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(grover_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(grover_test)
