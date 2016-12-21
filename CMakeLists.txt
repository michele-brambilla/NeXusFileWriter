cmake_minimum_required (VERSION 2.6)
set(PROJECT_NAME_STR NeXusFileWriter)
project(${PROJECT_NAME_STR} CXX)

# The version number.
set (neventGenerator_VERSION_MAJOR 0)
set (neventGenerator_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS "-std=c++11 -D_GLIBCXX_USE_NANOSLEEP ${CMAKE_CXX_FLAGS} -ggdb")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_custom_target(
  extern_lib
  COMMAND make
)

# add the binary tree to the search path for include files
include_directories( ${PROJECT_SOURCE_DIR} ${RDKAFKA_DIR}/include )

link_directories("${RDKAFKA_DIR}/lib")

add_library( NeXusFileWriter Streamer.cxx)

add_executable(test test.cxx)
target_link_libraries (test rdkafka rdkafka++ NeXusFileWriter)

include( CTest )

enable_testing()
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)
add_subdirectory (test)
