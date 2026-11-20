add_executable(query_algorithms query_algorithms.cpp)
target_link_libraries(query_algorithms PRIVATE qpp_headers)
target_compile_options(query_algorithms PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(query_algorithms_test query_algorithms_test.cpp)
target_link_libraries(query_algorithms_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(query_algorithms_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(query_algorithms_test)
