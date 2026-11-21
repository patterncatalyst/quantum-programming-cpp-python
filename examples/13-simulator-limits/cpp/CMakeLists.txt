add_executable(simulator_limits simulator_limits.cpp)
target_link_libraries(simulator_limits PRIVATE qpp_headers)
target_compile_options(simulator_limits PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(simulator_limits_test simulator_limits_test.cpp)
target_link_libraries(simulator_limits_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(simulator_limits_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(simulator_limits_test)
