set(TEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests)

include_directories (
  ${PROJECT_SOURCE_DIR}
  ${TEST_SOURCE_DIR}
  ) 

add_executable (streamer_test streamer_test.cxx) 
add_executable (streammaster_test streammaster_test.cxx) 

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

target_link_libraries( streamer_test
		       ${GTEST_BOTH_LIBRARIES}
		       rdkafka
		       rdkafka++
                       NeXusFileWriter)

target_link_libraries( streammaster_test
		       ${GTEST_BOTH_LIBRARIES}
		       rdkafka
		       rdkafka++
                       NeXusFileWriter)

add_test(NAME streamer_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/streamer_test)
add_test(NAME streammaster_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/streammaster_test)
