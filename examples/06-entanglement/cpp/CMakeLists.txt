add_executable(entanglement entanglement.cpp)
target_link_libraries(entanglement PRIVATE qpp_headers)
target_compile_options(entanglement PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(entanglement_test entanglement_test.cpp)
target_link_libraries(entanglement_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(entanglement_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(entanglement_test)
