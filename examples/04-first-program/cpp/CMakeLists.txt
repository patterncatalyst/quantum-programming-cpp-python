add_executable(coin_flip coin_flip.cpp)
target_link_libraries(coin_flip PRIVATE qpp_headers)
target_compile_options(coin_flip PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(coin_flip_test coin_flip_test.cpp)
target_link_libraries(coin_flip_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(coin_flip_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(coin_flip_test)
