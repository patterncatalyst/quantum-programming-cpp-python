add_executable(framework_demo framework_demo.cpp)
target_link_libraries(framework_demo PRIVATE qpp_headers)
target_compile_options(framework_demo PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(framework_demo_test framework_demo_test.cpp)
target_link_libraries(framework_demo_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(framework_demo_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(framework_demo_test)
