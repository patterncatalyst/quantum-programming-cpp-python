add_executable(bell_state bell_state.cpp)
target_link_libraries(bell_state PRIVATE qpp_headers)
target_compile_options(bell_state PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(bell_state_test bell_state_test.cpp)
target_link_libraries(bell_state_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(bell_state_test PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(bell_state_test)
