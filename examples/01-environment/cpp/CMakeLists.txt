add_executable(environment environment.cpp)
target_link_libraries(environment PRIVATE qpp_headers)
target_compile_options(environment PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(environment_test environment_test.cpp)
target_link_libraries(environment_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(environment_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(environment_test)
