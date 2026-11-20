add_executable(shor shor.cpp)
target_link_libraries(shor PRIVATE qpp_headers)
target_compile_options(shor PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(shor_test shor_test.cpp)
target_link_libraries(shor_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(shor_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(shor_test)
