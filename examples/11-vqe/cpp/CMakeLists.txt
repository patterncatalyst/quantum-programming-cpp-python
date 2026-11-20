add_executable(vqe vqe.cpp)
target_link_libraries(vqe PRIVATE qpp_headers)
target_compile_options(vqe PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(vqe_test vqe_test.cpp)
target_link_libraries(vqe_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(vqe_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(vqe_test)
