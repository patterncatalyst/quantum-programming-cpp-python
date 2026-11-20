cmake_minimum_required(VERSION 3.24)
project(quantum_examples CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies: Eigen and GoogleTest come from Conan; Quantum++ is header-only
# and pulled directly from its upstream release tag.
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

include(FetchContent)
FetchContent_Declare(
  qpp
  GIT_REPOSITORY https://github.com/softwareQinc/qpp.git
  GIT_TAG v7.1.1
  # Header-only: populate the sources but do not add qpp's own CMake build.
  SOURCE_SUBDIR do-not-build
)
FetchContent_MakeAvailable(qpp)

# One INTERFACE target the examples link against. qpp and Eigen headers are
# marked SYSTEM so their warnings never trip our warnings-as-errors.
add_library(qpp_headers INTERFACE)
target_include_directories(qpp_headers SYSTEM INTERFACE
  ${qpp_SOURCE_DIR}/include
  ${qpp_SOURCE_DIR}/qasmtools/include)
target_link_libraries(qpp_headers INTERFACE Eigen3::Eigen)
target_compile_features(qpp_headers INTERFACE cxx_std_23)

enable_testing()
include(GoogleTest)
add_subdirectory(00-setup/cpp)
add_subdirectory(01-environment/cpp)
add_subdirectory(02-qubits/cpp)
add_subdirectory(03-gates/cpp)
add_subdirectory(04-first-program/cpp)
add_subdirectory(05-measurement/cpp)
add_subdirectory(06-entanglement/cpp)
add_subdirectory(07-query-algorithms/cpp)
add_subdirectory(08-grover/cpp)
