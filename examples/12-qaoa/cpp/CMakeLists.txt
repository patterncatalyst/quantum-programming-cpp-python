add_executable(qaoa qaoa.cpp)
target_link_libraries(qaoa PRIVATE qpp_headers)
target_compile_options(qaoa PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(qaoa_test qaoa_test.cpp)
target_link_libraries(qaoa_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(qaoa_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(qaoa_test)
