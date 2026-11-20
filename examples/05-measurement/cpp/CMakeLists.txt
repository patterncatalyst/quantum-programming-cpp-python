add_executable(weighted_coin weighted_coin.cpp)
target_link_libraries(weighted_coin PRIVATE qpp_headers)
target_compile_options(weighted_coin PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(weighted_coin_test weighted_coin_test.cpp)
target_link_libraries(weighted_coin_test PRIVATE qpp_headers GTest::gtest_main)
target_compile_options(weighted_coin_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(weighted_coin_test)
