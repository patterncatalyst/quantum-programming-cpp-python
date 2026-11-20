# The from-scratch qubit uses only the standard library, no quantum headers.
add_executable(qubit qubit.cpp)
target_compile_options(qubit PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(qubit_test qubit_test.cpp)
target_link_libraries(qubit_test PRIVATE GTest::gtest_main)
target_compile_options(qubit_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
gtest_discover_tests(qubit_test)
