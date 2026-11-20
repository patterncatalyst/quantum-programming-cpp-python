add_executable(gates gates.cpp)
target_link_libraries(gates PRIVATE qpp_headers)
target_compile_options(gates PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(gates_test gates_test.cpp)
target_link_libraries(gates_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(gates_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(gates_test)
