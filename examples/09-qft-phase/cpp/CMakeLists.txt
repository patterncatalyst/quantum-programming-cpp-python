add_executable(phase_estimation phase_estimation.cpp)
target_link_libraries(phase_estimation PRIVATE qpp_headers)
target_compile_options(phase_estimation PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(phase_estimation_test phase_estimation_test.cpp)
target_link_libraries(phase_estimation_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(phase_estimation_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(phase_estimation_test)
